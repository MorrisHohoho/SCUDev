using UnityEngine;

public class ShadowSprites : MonoBehaviour
{
    private Transform player;

    private SpriteRenderer thisSprite;  //当前残影的图像帧
    private SpriteRenderer playerSprite;    //当前玩家的图像帧

    private Color color;    //render的color

   
    public float activeTime;
    float activeStart;

    private float alpha;
    public float alphaSet;  //alpha初始值
    public float alphaMul;

    private void OnEnable()
    {
        player = GameObject.FindGameObjectWithTag("Player").transform;
        thisSprite = GetComponent<SpriteRenderer>();
        playerSprite = player.GetComponent<SpriteRenderer>();

        alpha = alphaSet;

        thisSprite.sprite = playerSprite.sprite;
        transform.position = player.position;
        transform.localScale = player.localScale;
        transform.rotation = player.rotation;
        activeStart = Time.time;
    }

    private void FixedUpdate()
    {
        alpha *=alphaMul;
        color = new Color(0.5f, 0.5f, 1, alpha);

        thisSprite.color = color;

        if(Time.time>= activeStart + activeTime)
        {
            //返回对象池
            ShadowPool.instance.ReturnPool(this.gameObject);
        }
    }
}
