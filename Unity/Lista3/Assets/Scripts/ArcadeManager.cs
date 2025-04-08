using UnityEngine;
using TMPro;
using System;

public class ArcadeManager : MonoBehaviour
{
    public TextMeshProUGUI timerText;
    public AudioClip alertSound;
    public bool gameOver;
    private float timeLimit = 60f;
    private float remainingTime;
    private AudioSource audioSource;
    private string[] helper = new string[] { "", "!", "!!", "!!!" };
    private int lastPlayedSecond = -1;

    private void Start()
    {
        audioSource = GetComponent<AudioSource>();
        remainingTime = timeLimit;
        gameOver = false;
    }

    private void Update()
    {
        if (gameOver)
            return;
        
        
        remainingTime -= Time.deltaTime;

        if (remainingTime >= 0){
            timerText.text = Mathf.Ceil(remainingTime).ToString() + "s";
        }
        if (remainingTime < 0 && remainingTime >= -3){
            int currentSecond = Mathf.Abs((int)remainingTime);

            if (currentSecond != lastPlayedSecond)
            {
                audioSource.volume = 0.1f;
                audioSource.PlayOneShot(alertSound);
                lastPlayedSecond = currentSecond;
            }
            timerText.color = Color.red;
            timerText.text = 0.ToString() + helper[Math.Abs((int)remainingTime) + 1];
        }

        if (remainingTime < -3)
        {
            EndGame(); 
        }
    }

    private void EndGame(){
        gameOver = true;
    }

}
