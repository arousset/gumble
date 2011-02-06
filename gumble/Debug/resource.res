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

Texture back4
{
 filename=bgj4.jpg
}

Texture backfin
{
 filename=bgfin.jpg
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
 rect=0, 0, 213, 42 
}

Texture gameover
{
 filename=gameover.png
}

Texture lafrog
{
 filename=frogg.png
}

Animation frog
{
 texture=lafrog
 rect=0, 0, 123, 83
 frames=2
 fps=2
 mode=FORWARD,LOOP,PINGPONG
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

Sprite bgdelafin
{
 texture=backfin
 rect=0, 0, 800, 600
}


Sprite blevel4
{
 texture=back4
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

Stream theme_menu
{
 filename=menu.mp3
}

Stream legameover
{
 filename=gameover.mp3
}

<<<<<<< .mine
Stream lafin
{
 filename=fin.mp3
}

Stream mlevel1
{
 filename=l1.mp3
}

Stream mlevel2
{
 filename=l2.mp3
}

Stream mlevel3
{
 filename=l3.mp3
}

Stream mlevel4
{
 filename=l4.mp3
}

=======
Stream lafin
{
 filename=fin.mp3
}

Stream mlevel4
{
 filename=l4.mp3
}

>>>>>>> .r90
Stream lewin
{
 filename=win.wav
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
}

Sprite particleSprite2
{
 texture=particleTexture
 rect=96, 64, 32, 32
}

Particle particle_bulles
{
 filename=particle_bulles.psi
 sprite=particleSprite2
}