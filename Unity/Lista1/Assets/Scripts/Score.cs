using TMPro;
using UnityEngine;
using UnityEngine.UI;

public class Score : MonoBehaviour
{
    public Transform player;
    public TMP_Text ScoreText;
    void Update()
    {
        ScoreText.text = player.position.z.ToString("0");
    }
}
