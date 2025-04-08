using TMPro;
using UnityEngine;
using UnityEngine.UI;

public class Receiver : MonoBehaviour
{
    public TextMeshProUGUI targetText;
    public AudioClip womp;
    private AudioSource audioSource;

    void Awake(){
        audioSource = GetComponent<AudioSource>();
    }

    void Start()
    {
        if (targetText != null)
        {
            string receivedData = PlayerPrefs.GetString("PassedData");
            if (receivedData == "GAME OVER"){
                audioSource.volume = 0.3f;
                audioSource.PlayOneShot(womp);
            }
            targetText.text = receivedData;
        }
    }
}