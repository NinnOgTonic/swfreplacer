# Introduction #

This tool lets you to change the Texts (The DefineEditText tag which is Dynamic text not Static text), Images (DefineJPEG2 tag), and MovieClips (DefineSprite tag) inside a given SWF file.

If you can use this tool, you can change the precompiled SWF contents even though you don't have source (**.fla) file for those. And because you can repeatedly change the movie clip inside the given SWF file with another SWF file, you can even make more sophisticated one by comprising some number of small SWF movie files. (Generating SWF contents dynamically as per the user's request in Mobile phone Web services will be a good example).**


Currently ( Nov 10th 2009 ), this supports under Flash8, which is usually for FlashLite. And I haven't written codes for Sounds and Movie stream. And this does not support file compression yet.


I've tested compilation of this project on MS-Windows and Mac(Snow Leopard), and it is working nicely. But because this is the initial release, there can be many unknown bugs.


# Details #

This tool requires to command line arguments. The first one is for the template SWF file of which content you want to change , and the next one is for the new modified output SWF file.

For example, this command will change inner content of 'sample.swf' file and the result will be saved to 'a.swf'.

```
swfreplacer.exe sample.swf a.swf
```

If you run the program, it will first print out the the information of the given template SWF itself. In this process, it will extract image files inside the SWF file to the current directory.

And then, this program will wait for your commands. If you see this command prompt, you can type in 'help' for the list of commands this program currently understands.

```
> help
```

Currently this understands 4 simple commands.

  * txt : Replace a text (dynamic text).
  * img : Replace an image.
  * sprite : Replace a sprite (movie clip).
  * start : start conversion and save it to a result file.

Except the 'start' command (which is the final command for the command line), you can enter all this commands multiple times you want.


So, let's start how you can change those by an example.

In the root directory of this source code, you can see 'sample.fla' file. If you open it with Adobe Flash (CS4), then you will see this.

![http://brucewangkorea.googlegroups.com/web/swfre_1.png](http://brucewangkorea.googlegroups.com/web/swfre_1.png)

It has a DynamicText, and an image resource with Export name 'img1.jpg', and finally a Sprite (movie clip) with Export name 'movie1'.

## Replace a text ##
Let's start how we can change a text in SWF file. If you see following image, you will see a DynamicText selected, and the property of it says its **Variable Name** is [/:url]

![http://brucewangkorea.googlegroups.com/web/swfre_2.png](http://brucewangkorea.googlegroups.com/web/swfre_2.png)

And if you see following image, you can see there is a **Button**, which refers to the variable [/:url] and if you click on that button, the ActionScript will guide you to the URL written in that variable.

![http://brucewangkorea.googlegroups.com/web/swfre_3.png](http://brucewangkorea.googlegroups.com/web/swfre_3.png)

So, if you want to change the URL where the SWF direct, you type in this command to the program

```
txt "/:url" "http://iambrucewang.blogspot.com"
```

## Replace an image ##

Now if you see the first image again, you will see there is an image resource, of which Export name is [img1.jpg].

![http://brucewangkorea.googlegroups.com/web/swfre_1.png](http://brucewangkorea.googlegroups.com/web/swfre_1.png)

**Export name** is the tag which this program searches, so if you want to change that image resource, you type in following command.

```
img img1.jpg b.jpg
```

This will replace the image having [img1.jpg] Export name with the given new [b.jpg] file in the current directory.

## Replace a Sprite ##

Now if you see the following image, you will see there is a blank, square Sprite with Export name [movie1](movie1.md).

![http://brucewangkorea.googlegroups.com/web/swfre_4.png](http://brucewangkorea.googlegroups.com/web/swfre_4.png)

Let's say you want to replace that ugly Sprite with your new Sprite. Then you just make a new SWF file like this.

![http://brucewangkorea.googlegroups.com/web/swfre_5.png](http://brucewangkorea.googlegroups.com/web/swfre_5.png)

There is an alien movie clip, and its center is located at the position 0, 0. Let's say you generated movie1.swf file from that new Flash project.

Now if you want to replace the original blank movie clip with this new one, you type in following command.

```
sprite movie1 movie1.swf
```

This program will read in the new SWF file you gave, and print out the information for that new movie file.


## Convert them all ##
Now type in the 'start' command to the command line prompt.

```
start
```

Then this program will show the new content of modified SWF file and it will be saved to a new SWF file which you gave to the **swfreplacer** program.

Now this is the result..
http://brucewangkorea.googlegroups.com/web/a.swf?gda=zT0ECjgAAACU1SScV0-5gXUmLEWmXD3Q7Twi5XPUqmGDZFIiTrcAgQsV_c6CwoPSGKXvqhTip6IaNWB3A2L4HCtTMEZPaE7O&gsc=1OjqYQsAAADmiTccD1atSsbJuwVI0i6o

# So.. #

This is not commercial one. Please read the license (Apache 2.0). I am not responsible for any problems you have when you use my tool in your commercial activities.

And I hope I can have participants who can improve this project together. You can also support me in any ways.

If you are aiming for the PC browsers only, you don't need this tool at all. You can dynamically load movie clips, no problem. So this maybe old-fashioned. But I just hope this can be useful for somebody.

Cheers.

Bruce Wang.