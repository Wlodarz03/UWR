using TMPro;
using Unity.VisualScripting;
using UnityEngine;
using UnityEngine.Android;
using UnityEngine.UI;
using System.Collections.Generic;
using UnityEngine.SceneManagement;
using System.Linq;
using System.Collections;
using UnityEditor;

public class BallController : MonoBehaviour
{   
    public AudioClip hitSound;
    public AudioClip victorySound;
    public AudioClip failSound;
    public float maxPower;
    public float changeAngleSpeed;
    public float lineLength;
    public float minHoleTime;
    public Slider powerSlider;
    public TextMeshProUGUI puttCountLabel;
    public ArcadeManager arcade;

    private AudioSource audioSource;
    private List<Renderer> hiddenObjects = new List<Renderer>();
    private Dictionary<Renderer, float> originalAlphas = new Dictionary<Renderer, float>();
    private LineRenderer line;
    private Rigidbody ball;
    private float angle;
    private float powerUpTime;
    private float power;
    private int putts;
    private int allPutts;
    private float holeTime;
    private Vector3 lastPosition;
    private bool finished;

    private void Awake(){
        ball = GetComponent<Rigidbody>();
        line = GetComponent<LineRenderer>();
        audioSource = GetComponent<AudioSource>();
        ball.maxAngularVelocity = 1000;
        finished = false;
        putts = 0;
        if (PlayerPrefs.HasKey("AllPutts")){
            allPutts = PlayerPrefs.GetInt("AllPutts");
        }
        else{
            allPutts = 0;
        }
        
        PlayerPrefs.SetInt("CurrentSceneIndex", SceneManager.GetActiveScene().buildIndex);
        PlayerPrefs.SetInt("AllPutts", allPutts);
        PlayerPrefs.Save();
    }

    private void EndGameWithGameOverMessage()
    {
        string gameOverMessage = "GAME OVER";
        PlayerPrefs.SetString("PassedData", gameOverMessage);
        PlayerPrefs.Save();
        SceneManager.LoadScene(SceneManager.sceneCountInBuildSettings - 2);
    }

    void Update(){
        if (arcade != null && arcade.gameOver)
        {
            EndGameWithGameOverMessage();
            return;
        }
        if (Input.GetKey(KeyCode.Escape)){
            PlayerPrefs.SetInt("Putts", putts);
            PlayerPrefs.Save();
            SceneManager.LoadScene(SceneManager.sceneCountInBuildSettings-1);
        }

        if (ball.linearVelocity.magnitude < 0.01f){
            CheckObstacles();
            if (Input.GetKey(KeyCode.A)){
                ChangeAngle(-1);
            }

            if (Input.GetKey(KeyCode.D)){
                ChangeAngle(1);
            }

            if (Input.GetKeyUp(KeyCode.Space)){
                if (powerSlider.value < 0.3){
                    audioSource.volume = 0.3f;
                }
                else{
                    audioSource.volume = 0.8f;
                }
                audioSource.PlayOneShot(hitSound);
                Putt();
            }

            if (Input.GetKey(KeyCode.Space)){
                PowerUp();
            }

            UpdateLinePositions();
        }
        else{
            line.enabled = false;
        }
        
    }
    

    private void ChangeAngle(int direction){
        angle += changeAngleSpeed * Time.deltaTime * direction; // direction = 1 lub -1
    }

    private void UpdateLinePositions(){
        if (holeTime == 0 && !finished){
            line.enabled = true;
        }

        Vector3 startPosition = transform.position; 
        line.SetPosition(0, startPosition);

        Vector3 direction = Quaternion.Euler(0, angle, 0) * Vector3.forward;
        Vector3 targetPosition = startPosition + direction * lineLength;

        RaycastHit hit;
        if (Physics.Raycast(startPosition, direction, out hit, lineLength)){
            targetPosition = hit.point;
        }

        line.SetPosition(1, targetPosition);
    }

    private void Putt(){
        ClearHiddenObjects();
        lastPosition = transform.position;
        ball.AddForce(Quaternion.Euler(0, angle, 0) * Vector3.forward * maxPower * power, ForceMode.Impulse);
        power = 0;
        powerSlider.value = 0;
        powerUpTime = 0;
        putts++;
        allPutts++;
        PlayerPrefs.SetInt("AllPutts", allPutts);
        PlayerPrefs.Save(); 
        puttCountLabel.text = putts.ToString();
    }

    private void PowerUp(){
        powerUpTime += Time.deltaTime;
        power = Mathf.PingPong(powerUpTime, 1);
        powerSlider.value = power;
    }

    void OnTriggerStay(Collider other){
        if (other.tag == "Hole"){
            CountHoleTime();
        }
    }

    private IEnumerator PlayVictorySoundAndLoadScene() {
        audioSource.PlayOneShot(victorySound);
        yield return new WaitForSeconds(victorySound.length - 2f); // Czekaj na zakończenie dźwięku
        SceneManager.LoadScene(SceneManager.GetActiveScene().buildIndex + 1);
    }

    private void CountHoleTime(){
        holeTime += Time.deltaTime;
        if (holeTime >= minHoleTime){
            finished = true;
            Debug.Log("Jestem w dziurze, po " + putts + " ruchach.");
            PlayerPrefs.SetInt("AllPutts", allPutts);
            PlayerPrefs.Save(); 
            putts = 0;
            holeTime = 0;
            if (SceneManager.GetActiveScene().buildIndex == SceneManager.sceneCountInBuildSettings-3){ // scene.Count-1 scena na pauze, scene.Count-2 scena na END
                string s = "KONIEC GRY \n ŁĄCZNIE: " + allPutts + " RUCHÓW";
                PlayerPrefs.SetString("PassedData", s);
                PlayerPrefs.Save();
            }
            StartCoroutine(PlayVictorySoundAndLoadScene());
        }
    }

    void OnTriggerExit(Collider other){
        if (other.tag == "Hole"){
            LeftHole();
        }
    }

    private void LeftHole(){
        holeTime = 0;
    }

    private void OnCollisionEnter(Collision collision){
        if (collision.collider.tag == "Out"){
            audioSource.PlayOneShot(failSound);
            transform.position = lastPosition;
            ball.linearVelocity = Vector3.zero;
            ball.angularVelocity = Vector3.zero;
        }
    }

    private void SetAlpha(Renderer renderer, float alpha)
    {
        Material[] materials = renderer.materials;
        foreach (var material in materials)
        {
            if (!originalAlphas.ContainsKey(renderer))
            {
                originalAlphas[renderer] = renderer.material.color.a;
            }

            if (material.GetFloat("_Mode") != 2) // 2 = Fade
            {
                material.SetFloat("_Mode", 2); // Ustaw tryb na Fade
                material.SetInt("_SrcBlend", (int)UnityEngine.Rendering.BlendMode.SrcAlpha);
                material.SetInt("_DstBlend", (int)UnityEngine.Rendering.BlendMode.OneMinusSrcAlpha);
                material.SetInt("_ZWrite", 1);
                material.DisableKeyword("_ALPHATEST_ON");
                material.EnableKeyword("_ALPHABLEND_ON");
                material.DisableKeyword("_ALPHAPREMULTIPLY_ON");
                material.renderQueue = (int)UnityEngine.Rendering.RenderQueue.Transparent; // Transparent render queue
            }

            if (material.HasProperty("_Color"))
            {
                Color color = material.color;
                color.a = alpha;
                material.color = color;
            }
        }
    }

    private void CheckObstacles(){
        if (ball.linearVelocity.magnitude > 0.01f) return;
        ClearHiddenObjects();
        hiddenObjects.Clear();

        Camera mainCamera = Camera.main;
        if (!mainCamera) return;

        Vector3 ballPosition = transform.position;
        Vector3 cameraPosition = mainCamera.transform.position;
        Vector3 direction = ballPosition - cameraPosition;

        float radius = 0.01f;

        RaycastHit[] hits = Physics.SphereCastAll(cameraPosition, radius, direction, direction.magnitude);

        foreach (var hit in hits)
        {
            if (hit.collider.gameObject == gameObject) continue;

            Renderer renderer = hit.collider.GetComponent<Renderer>();
            if (renderer != null)
            {
                hiddenObjects.Add(renderer);
                SetAlpha(renderer, 0.5f);
            }
        }
    }
    private void ClearHiddenObjects(){
        foreach (var renderer in hiddenObjects)
        {
            SetAlpha(renderer, originalAlphas[renderer]);
        }
        hiddenObjects.Clear();
    }
}
