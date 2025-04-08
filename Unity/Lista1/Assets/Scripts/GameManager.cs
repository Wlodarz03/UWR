using System;
using UnityEngine;
using UnityEngine.SceneManagement;

public class GameManager : MonoBehaviour
{
    bool GameHasEnded = false;
    public float RestartDelay = 1f;

    public GameObject CompleteLevelUI;

    public void CompleteLevel()
    {
        CompleteLevelUI.SetActive(true);
    }
    public void EndGame()
    {
        if (!GameHasEnded){
            GameHasEnded = true;
            Debug.Log("GAME OVER");
            Invoke("Restart", RestartDelay);
        }  
    }

    void Restart()
    {
        SceneManager.LoadScene(SceneManager.GetActiveScene().name);
    }
}
