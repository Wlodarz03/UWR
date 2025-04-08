using UnityEngine;

public class PlayerCollision : MonoBehaviour
{
    public Movement movement;
    void OnCollisionEnter(Collision info)
    {
        if (info.collider.tag == "Obstacle")
        {
            movement.enabled = false;
            FindObjectOfType<GameManager>().EndGame();
        }
    }
}
