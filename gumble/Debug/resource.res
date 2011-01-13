Texture backg
{
 filename=bgintro.jpg
}

Sprite bgg
{
 texture=backg
 rect=0, 0, 800, 600
}

Texture background
{
 filename=bgj.jpg
}
Texture anim_bt
{
 filename=anim_bt.png
}

Animation bt_anim
{
 texture=anim_bt
 rect=0, 0, 130, 124
 frames=2
 fps=4
 mode=FORWARD
}

Texture canon
{
 filename=Cannon.png
}

Sprite img_canon
{
 texture=canon
 rect=0,0,130,130
}

Texture youwin
{
 filename=youwin.png
}

Sprite you_win
{
 texture=youwin
 rect=0, 0, 231, 42 
}

Texture gameover
{
 filename=gameover.png
}

Sprite game_over
{
 texture=gameover
 rect=0, 0, 276, 43
}

Sprite bgSprite
{
 texture=background
 rect=0, 0, 800, 600
}

Texture boule
{
 filename=boule.png
}

Animation br
{
 texture=boule
 rect=0, 0, 32, 32
 frames=4
 fps=4
 mode=FORWARD,LOOP,PINGPONG
}

Animation bj
{
 texture=boule
 rect=0, 32, 32, 32
 frames=4
 fps=4
 mode=FORWARD,LOOP,PINGPONG
}


Animation bo
{
 texture=boule
 rect= 0, 64, 32, 32
 frames=4
 fps=6
 mode=FORWARD,LOOP,PINGPONG
}


Animation bb
{
 texture=boule
 rect=0, 96, 32, 32
 frames=4
 fps=3
 mode=FORWARD,LOOP,PINGPONG
}

Animation bv
{
 texture=boule
 rect=0, 128, 32, 32
 frames=4
 fps=2
 mode=FORWARD,LOOP,PINGPONG
}

Animation bvi
{
 texture=boule
 rect=0, 160, 32, 32
 frames=4
 fps=2
 mode=FORWARD,LOOP,PINGPONG
}

Animation bgris
{
 texture=boule
 rect=0, 192, 32, 32
 frames=4
 fps=2
 mode=FORWARD,LOOP,PINGPONG
}

Stream theme
{
 filename=music.mp3
}

Font font1
{
 filename=font1.fnt
}

Texture particleTexture
{
 filename=particles.png
}

Sprite particleSprite
{
 texture=particleTexture
 rect=32, 64, 32, 32
}

Particle particle
{
 filename=particle.psi
 sprite=particleSprite
 fps=50.0
}