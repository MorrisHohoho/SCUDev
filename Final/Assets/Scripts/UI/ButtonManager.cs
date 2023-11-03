using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class ButtonManager : MonoBehaviour
{
  public void StartMenu()
    {
        SceneManager.LoadScene("Map1");
    }

    public void OnApplicationQuit()
    {
        Application.Quit();
    }
}
