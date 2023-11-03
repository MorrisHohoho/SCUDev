using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class GameManager : MonoBehaviour
{
    [SerializeField] float resetTime = 1.0f;
    [SerializeField] PlayerController player;
    [SerializeField] Transform diePos;
    Vector2 playerPos;
    private void Update()
    {
        playerPos = player.GetPlayerCoord();
        if (playerPos.y < diePos.position.y)
        {
            player.setPlayerLife(false);
            player.SetVelocity(Vector2.zero);
            player.unableGravity();
            Invoke(nameof(Restart), resetTime);
        }

    }
    private void Restart()
    {
        SceneManager.LoadScene(SceneManager.GetActiveScene().buildIndex);
    }
}
