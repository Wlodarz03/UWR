using System.Numerics;
using UnityEngine;
using UnityEngine.SceneManagement;

public class PauseManager : MonoBehaviour
{
    private int currentSceneIndex;
    private int Putts;
    private int AllPutts;
    void Start(){
        currentSceneIndex = PlayerPrefs.GetInt("CurrentSceneIndex");
        AllPutts = PlayerPrefs.GetInt("AllPutts");
        Putts = PlayerPrefs.GetInt("Putts");
    }
    void Update()
    {
        if (Input.GetKey(KeyCode.Escape)){
            PlayerPrefs.SetInt("AllPutts", AllPutts - Putts);
            SceneManager.LoadScene(currentSceneIndex);
            Debug.Log("WCISKAM I CHCE WROCIC DO: "+ currentSceneIndex);
        }
    }
}
