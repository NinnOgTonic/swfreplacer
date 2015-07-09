> # 紹介 #


このツールを使うと、すでに有るSWFファイルの中のテキスト（DefineEditText）や
イメージ（DefineJPEG2）、ムービクリップ（DefineSprite）を差し替えることが出来ます。

だからフラッシュファイルのソース(**.fla)が無くてもそのSWFファイルの中身が
変更出来ます。そして、その差し替えを何度もすることが出来ますので
小さいSWFファイルらを使って、もっと大きくて複雑なSWFファイルを作るのも出来ます。
例えば、携帯用のフラッシュファイルを自動的に作成することも出来ます。**

現在（２００９年１１月）はこのツールはFlash8以下のバージョン（FlashLite）がサポ＾とされます。
そしてサウンドとかムービストリムの為のコードは有りません。

このツールはMSウインドーとMac(Snow Leopard)でコンパイルと実行が出来ることを確認しました。
まだ初めてのソースコードのコミットしたばかりですのできっと、私は知らなかったバーグが
有るようですよね。

> # Details #

このツールはコマンドラインで使います。使用するアーギュメントは２つ。先ずは
変換したいSWF（テンプレートファイルと言いましょう）、次はその変更結果を貯蔵する
結果ファイルの名です。

例えば、次の命令は「sample.swf」ファイルを変更してその結果を「a.swf」ファイルに貯蔵します。


> ` swfreplacer.exe sample.swf a.swf `

このプログラムを実行しますと、このツールは先ずテンプレートSWFファイルの中身の
情報を表示します。このステップの間にはSWFファイルの中のイメージファイルが
現在のフォールだに貯蔵されます。　その後、あなたの命令の入力を待ちます。

この命令プロンプトで「help」と言う命令を入力しますと、このツールが現在解析出来る
命令の目録が表示されます。

> ` > help `

現在は次の４つの命令が使われます。


  * txt :　テキスト(dynamic text)を差し替えます。
  * img :　イメージをを差し替えます。
  * sprite :　スプライト(movie clip)を差し替えます。
**start :　変更作業を始めます。**

「start」命令以外の命令は何度も使えます。


じゃあ、どうやって使うのがは次の例を見ながら確認しましょう。


このプロジェクトのルートフォルダには「sample.fla」ファイル（dobe Flash CS4)が
有ります。これを開けましょう。


> ![http://brucewangkorea.googlegroups.com/web/swfre_1.png](http://brucewangkorea.googlegroups.com/web/swfre_1.png)

このフラッシュファイルにはDynamicTextとイメージ（エキスポート名がimg1.jpg）、
そしてムービクリップ（エキスポート名がmovie1）が有るのが分かりますね。


> ## テキストの差し替え ##

では、テキストを差し替えましょう。次の画像を見ますと変数名が[/:url]である
ダイナミックテキストが見えます。


> ![http://brucewangkorea.googlegroups.com/web/swfre_2.png](http://brucewangkorea.googlegroups.com/web/swfre_2.png)

そして、次の画像を見ますと先の[/:url]変数を参考してその変数の内容の
URLに移動するActionScriptが有るバトンが見えます。


> ![http://brucewangkorea.googlegroups.com/web/swfre_3.png](http://brucewangkorea.googlegroups.com/web/swfre_3.png)

だから、このSWFファイルが移動するURL先を変更したい時にはこのツールの
命令プロンプトに次のような命令を入力します。

> ` txt "/:url" "http://iambrucewang.blogspot.com" `

> ## イメージの差し替え ##

今度は、先の画像をまた見ますとエキスポート名が[img1.jpg]である
イメージリソースが見えます。

> ![http://brucewangkorea.googlegroups.com/web/swfre_1.png](http://brucewangkorea.googlegroups.com/web/swfre_1.png)


このツールは\*エキスポート名**を探しますので、このイメージを差し替えたい
時のは次ぎなような命令を入力します。**

> ` img img1.jpg b.jpg `

上の命令は[img1.jpg]のエキスポート名のイメージを現在のフォルダにある[b.jpg]
ファイルで差し替えます。

> ## スプライトの差し替え ##

最後に、次の画像をみますと何も無い四角形のスプライトが見えます。そのエキスポート名は
[movie1](movie1.md)です。

> ![http://brucewangkorea.googlegroups.com/web/swfre_4.png](http://brucewangkorea.googlegroups.com/web/swfre_4.png)

この四角形のスプライトの代わりに使いたいSWFファイルを作りましょう。

> ![http://brucewangkorea.googlegroups.com/web/swfre_5.png](http://brucewangkorea.googlegroups.com/web/swfre_5.png)

エイリアンのイメージがあるこのSWFファイルをmovie1.swfファイルとして貯蔵しましょう。

では、先の四角形のスプライトの代わりに上のmovie1.swfで差し替えたい時には
次のような命令を入力します。

> ` sprite movie1 movie1.swf `

そうすると、このツールはmovie1.swfファイルの中身の内容を表示して、差し替えをします。


> ## 変更を始め ##

じゃあ、これまでの変更内容を実際のSWFファイルで貯蔵しましょう。

> ` start `

そうすると最初私たちが指定した結果ファイルにこれまでの変更が反映されて記録されます。

これがその結果ファイルです。

[http://brucewangkorea.googlegroups.com/web/a.swf?gda=zT0ECjgAAACU1SScV0-
5gXUmLEWmXD3Q7Twi5XPUqmGDZFIiTrcAgQsV\_c6CwoPSGKXvqhTip6IaNWB3A2L4HCtTMEZPaE7O&
gsc=1OjqYQsAAADmiTccD1atSsbJuwVI0i6o]

> # 結論 #

これはApache 2.0ライセンスの物です。私はあなたがこのツールをあなたの営業に使って
おこる問題には責任が有りません。その代わりにこのツールを自由で使っても良いです。

でも、このツールのコードとか実行ファイルを再配布する時には私の原作者の情報を
残ってなくては行けません。

自分の願いは、誰か私と力を合わせてこのプロジェクトをもっと発展することです。
そのプログラミング以外にもあなたが私をサポートすることは沢山有ります。



では、宜しくお願いいたします。

> Bruce Wang.