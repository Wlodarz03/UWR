using UnityEngine;

public class TreeSwing : MonoBehaviour
{
    private float swingSpeed = 2.5f;  // Szybkość kołysania
    private float swingAmount = 2.5f; // Maksymalny kąt wychylenia w stopniach

    private Quaternion initialRotation;

    void Start()
    {
        initialRotation = transform.localRotation;
    }

    void Update()
    {
        float angle = Mathf.Sin(Time.time * swingSpeed) * swingAmount;

        transform.localRotation = initialRotation * Quaternion.Euler(0, 0, angle);
    }
}
