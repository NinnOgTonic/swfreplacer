# 소개 #

이 프로그램은 이미 존재하는 SWF파일 내부의 텍스트(SWF파일 포멧의 DefineEditText 태그로 정의된 다이나믹 텍스트), 이미지 (DefineJPEG2 태그), 그리고 스프라이트 (DefineSprite 태그) 를 원하시는 내용으로 대체 할 수 있습니다.

이 툴을 사용하시면 가지고 계신 SWF파일의 소스(**.fla)파일이 없더라도 그 내부 내용을 바꿀 수 있고, 또 그 내부의 스프라이트(무비클립) 을 다른 SWF파일로 대체하는 등의 작업을 계속 반복할 수 있습니다. 따라서 간단한 여러개의 SWF파일들을 조합하여 보다 복잡한 기능을 가진 SWF파일을 만드시는 것이 가능합니다.**

휴대폰용 플래시 컨텐츠를 자동으로 서버에서 생성하셔야만 하는 경우가 그 좋은 예라고 할 수 있겠습니다.


현재(2009년 11월 10일) 이 툴은 Flash8미만의 버전 (즉 플래시 라이트) 을 지원합니다. 그리고 아직 사운드와 동화상스트림 태그에 대해서는 작성된 코드가 없습니다. 또한 SWF파일의 압축기능도 아직 제공하지 않습니다.

제가 가지고 있는 윈도우즈 시스템과 매킨토시(스노우 레오파드) 시스템에서 정상적으로 컴파일, 실행되는 것을 확인했습니다만, 이제 겨우 처음 소스 커밋이 된 상태이므로 제가 발견하지 못한 버그가 있을 수 있습니다.

# 상세 설명 #

이 툴은 명령행 프로그램으로, 두개의 아규먼트를 지정해 주셔야 합니다. 첫번째 아규먼트는 내용을 변경하시고자 하는 원본 SWF파일의 이름 (템플릿이라고 부르겠습니다), 그 다음 아규먼트는 변경하신 내용을 저장할 결과 SWF파일의 이름입니다.

예를 들어, 다음의 명령은 'sample.swf'파일 내부의 정보를 변경하여 그 결과를 'a.swf' 파일에 저장하게됩니다.

```
swfreplacer.exe sample.swf a.swf
```

이 프로그램을 실행하시면, 원본 SWF파일의 정보가 출력되는 것을 보실 수 있습니다. 이 과정에서 그 SWF파일에 들어 있는 JPEG이미지 리소스가 현재 작업중이신 디렉토리에 추출되어 저장되도록 하였습니다.

그 다음으로, 프로그램은 여러분의 명령 입력을 기다리게 됩니다. 다음의 코맨트 프롬프트를 보시게 된다면, 'help' 라는 명령을 입력하셔서 현재 이 툴이 지원하는 명령의 목록을 확인하실 수 있습니다.

```
> help
```

현재는 다음과 같은 4개의 간단한 명령들이 지원됩니다.

  * txt : 텍스트 내용을 치환합니다. (dynamic text).
  * img : 이미지를 치환합니다.
  * sprite : 스프라이트를 치환합니다. (movie clip).
  * start : 이상의 변경 내용을 새로운 파일에 직접 저장하고 끝냅니다.

'start' 명령 (이 프로그램에 입력하실 수 있는 제일 마지막 명령) 을 제외하고는 얼마든지 반복해서 입력이 가능합니다.

자, 이제 그럼 예제를 통해 어떻게 이 프로그램을 사용하시는지 알아보도록 하겠습니다.



이 프로그램의 소스코드 패키지의 루트 디렉토리에 보시면 'sample.fla' 라는 플래쉬 소스 파일(Flash CS4)이 들어 있습니다. 이 소스 파일을 열어보시면 다음 화면과 같을 것입니다.


![http://brucewangkorea.googlegroups.com/web/swfre_1.png](http://brucewangkorea.googlegroups.com/web/swfre_1.png)


이 플래쉬 파일은 DynamicText, 이미지 (엑스포트 이름이 'img1.jpg' 으로 되어 있을겁니다), 그리고 스프라이트(엑스포트 이름이 'movie1')가 들어 있습니다.

## 텍스트 변경 ##

그럼 SWF파일의 텍스트를 어떻게 변경하는지 알아보겠습니다. 다음 그림을 보시면 **변수명** 이 [/:url]인 DynamicText가 선택되어 있는 것이 보입니다.

![http://brucewangkorea.googlegroups.com/web/swfre_2.png](http://brucewangkorea.googlegroups.com/web/swfre_2.png)

그리고 다음 그림을 보시면, 앞서의 [/:url] 변수를 참조하여 그 변수 내용에 들어 있는 URL로 이동하게 하는 ActionScript 코드가 들어 있는 **버튼** 이 보입니다.

![http://brucewangkorea.googlegroups.com/web/swfre_3.png](http://brucewangkorea.googlegroups.com/web/swfre_3.png)

따라서,  이 SWF파일이 이동하게 될 URL정보를 변경하시고 싶다면, 다음과 같은 명령을 입력하시면 됩니다.


```
txt "/:url" "http://iambrucewang.blogspot.com"
```

## 이미지 변경 ##

다시 첫번째 그림을 보시면, 엑스포트 이름이 [img1.jpg]인 이미지가 보입니다.


![http://brucewangkorea.googlegroups.com/web/swfre_1.png](http://brucewangkorea.googlegroups.com/web/swfre_1.png)

**엑스포트 이름** 이란, 이 프로그램이 검색을 하는 공개된 이름으로서, 위의 그림 내용을 다른 그림파일로 대체하시고 싶을 경우는 다음과 같은 명령을 입력하시면 됩니다.

```
img img1.jpg b.jpg
```

위의 명령은  [img1.jpg] 라는 이름으로 엑스포트된 이미지를 현재 디렉토리에 존재하는  [b.jpg] 파일로 대체합니다.

## 스프라이트 대체 ##

이제 다음 그림을 보시면, 아무것도 없는 검은색 사각형 스프라이트가 보입니다. 그 스프라이트는  [movie1](movie1.md) 이라는 이름으로 엑스포트되어 있습니다.

![http://brucewangkorea.googlegroups.com/web/swfre_4.png](http://brucewangkorea.googlegroups.com/web/swfre_4.png)

이 스프라이트를 새로운 스프라이트로 대체하시고 싶다고 가정해 봅니다. 그 새로운 스프라이트를 한번 만들어 보겠습니다.

![http://brucewangkorea.googlegroups.com/web/swfre_5.png](http://brucewangkorea.googlegroups.com/web/swfre_5.png)

에이리언 그림의 중앙이 화면 0,0 포지션에 있군요. 이것을 movie1.swf 이라는 이름의 파일로 현재 디렉토리에 저장합니다.

이제, 앞서의 원래 검은 사각형 스프라이트를 이 새로운 movie1.swf 파일의 내용으로 대체하시고 싶다면 다음의 명령을 입력하시면 됩니다.

```
sprite movie1 movie1.swf
```

그러면 이 프로그램은 새로 대체하시려는 SWF파일의 내용을 출력하게 됩니다.

## 변경내용 저장 ##

이제  'start'명령을 입력하시면 지금까지의 변경 내용 전체가 앞서 이 프로그램을 시작하실 때 지정하셨던 결과 SWF파일로 저장됩니다.

```
start
```

다음이 바로 그 결과로 만들어진 파일입니다.

http://brucewangkorea.googlegroups.com/web/a.swf?gda=zT0ECjgAAACU1SScV0-5gXUmLEWmXD3Q7Twi5XPUqmGDZFIiTrcAgQsV_c6CwoPSGKXvqhTip6IaNWB3A2L4HCtTMEZPaE7O&gsc=1OjqYQsAAADmiTccD1atSsbJuwVI0i6o

# 결론 #

이 프로그램은 상용 프로그램이 아니고 Apache 2.0 라이선스를 따르고 있습니다. 간단히 말씀드리자면, 저는 이 프로그램을 여러분이 상업적인 용도로 사용하시다가 발생하는 문제에 대해 아무런 책임이 없습니다. 그 대신 여러분은 이 프로그램을 자유롭게 수정,사용 하실 수 있습니다. 한가지 조건은 소스코드/바이너리 배포시 원작자인 저의 정보와 라이센스 내용을 함께 배포하셔야 한다는 것입니다.

오래 된 기술일 지 모르겠지만, 누군가에게 유용한 프로그램, 코드였스면 좋겠습니다.

바램이 있다면, 저와 함께 이 프로젝트를 보다 근사하게 발전시킬 파트너가 있으면 하는 것입니다. 그리고 여러분께서는 여러가지 방법으로 저를 후원 해 주실 수 도 있겠습니다.

그럼, 관심 감사 드리며 이만 줄입니다.

Cheers.

Bruce Wang (왕성현).