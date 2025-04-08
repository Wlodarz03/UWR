using System.Security;
using UnityEngine;
using UnityEngine.SceneManagement;

public class Menu : MonoBehaviour
{  
    private int ALLPUTTS;
    private int CurrentSceneIndex;
    private int Putts;

    void Start(){
        ALLPUTTS = PlayerPrefs.GetInt("AllPutts");
        CurrentSceneIndex = PlayerPrefs.GetInt("CurrentSceneIndex");
        Putts = PlayerPrefs.GetInt("Putts");
    }

    public void StartGame(){
        SceneManager.LoadScene(SceneManager.GetActiveScene().buildIndex + 1);
        PlayerPrefs.SetInt("AllPutts", 0);
        PlayerPrefs.Save();
    }

    public void PlayAgain(){
        PlayerPrefs.SetInt("CurrentSceneIndex", SceneManager.GetActiveScene().buildIndex);
        PlayerPrefs.SetInt("AllPutts", 0);
        PlayerPrefs.Save();
        SceneManager.LoadScene(1);
    }

    public void Exit(){
        Application.Quit();
    }

    public void NextLevel(){
        ALLPUTTS += 20; // Kara za skip
        PlayerPrefs.SetInt("AllPutts", ALLPUTTS - Putts);
        PlayerPrefs.Save();
        int nextSceneIndex = CurrentSceneIndex + 1;

        if (nextSceneIndex < 7)
        {
            SceneManager.LoadScene(nextSceneIndex);
        }
        else if (nextSceneIndex == 7)
        {
            Debug.Log("To był ostatni level.");
            string s = "KONIEC GRY \n ŁĄCZNIE: " + ALLPUTTS + " RUCHÓW";
            PlayerPrefs.SetString("PassedData", s);
            SceneManager.LoadScene(nextSceneIndex);
        }
    }
}
