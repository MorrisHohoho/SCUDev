using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.InputSystem;

public class PlayerInput : MonoBehaviour
{
    InputActions playerInputActions;

    [SerializeField]float jumpInputBufferTime = 0.5f;

    WaitForSeconds waitJumpInputBufferTime;

    Vector2 axes => playerInputActions.Gameplay.Axes.ReadValue<Vector2>();
    public bool Jump => playerInputActions.Gameplay.Jump.WasPressedThisFrame();
    public bool StopJump => playerInputActions.Gameplay.Jump.WasReleasedThisFrame();
    public bool Move => AxisX != 0f;
    public float AxisX => axes.x;
    public float AxisY => axes.y;
    public bool Dash => playerInputActions.Gameplay.Dash.WasPressedThisFrame();

    public bool Climb => playerInputActions.Gameplay.Climb.IsPressed();
    public bool StopClimb => playerInputActions.Gameplay.Climb.WasReleasedThisFrame();

    public bool HasJumpInputBuffer { get; set; }

    void Awake()
    {
        playerInputActions = new InputActions();

        waitJumpInputBufferTime = new WaitForSeconds(jumpInputBufferTime);
    }

    private void OnEnable()
    {
        playerInputActions.Gameplay.Jump.canceled += delegate
        {
            HasJumpInputBuffer = false;
        };
    }
    public void EnableGameplayInputs()
    {
        playerInputActions.Gameplay.Enable();
        //Cursor.lockState = CursorLockMode.Locked;
    }

    public void DisableGameplayInputs()
    {
        playerInputActions.Gameplay.Disable();
    }

    public void SetJumpInputBufferTimer()
    {
        StopCoroutine(nameof(JumpInputBufferCoroutine));
        StartCoroutine(nameof(JumpInputBufferCoroutine));
    }
    IEnumerator JumpInputBufferCoroutine()
    {
        HasJumpInputBuffer = true;

        yield return waitJumpInputBufferTime;

        HasJumpInputBuffer = false;
    }
}
