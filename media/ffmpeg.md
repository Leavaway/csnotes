## ffplay
  播放控制: <br>
    q/ESC 推出播放; m 静音; p 暂停; 9/0 减少增加音量; a/v/t/c 循环切换音频流/视频流/字幕流/节目; s 逐帧播放<br/>
  主要命令: <br>
    -x width 强制显示宽带<br/>
    -y height 强制显示高度<br/>
    -video size size 尺寸 设置显示帧存储(WxH格式)，仅适用于类似原始YUV等没有包含帧大小(WxH)的视频。<br/>
      比如 : ffplay -pixel format yuv420p -video_size 320x240 -framerate 5 yuv420p 320x240.yuv<br/>
    -pixel format format 格式设置像素格式<br/>
    -fs 以全屏模式启动<br/>
    -an 禁用音频(不播放声音)<br/>
    -vn 禁用视频(不播放视频)<br/>
    -sn 禁用字幕(不显示字幕)<br/>
    -ss pos 根据设置的秒进行定位拖动，注意时间单位<br/>
      比如55'55-ss poSseconds,'12:03:45',12 hours, 03 minutes and 45 seconds23.189' 23.189second<br/>
    -t duration 设置播放视频/音频长度，时间单位如 <br/>
    -bytes 按字节进行定位拖动(0=off 1=on -1=auto)<br/>
    -seek intervalinterval 自定义左/右键定位拖动间隔 (以秒为单位)，默认值为10秒<br/>
    -nodisp 关闭图形化显示窗口，视频将不显示<br/>
    -noborder 无边框窗口<br/>
    -volume vol 设置起始音量。音量范围0~100<br/>
    -f fmt 强制使用设置的格式进行解析。比如-f s16le-f fmt-window_title title 设置窗口标题(默认为输入文件名)<br/>
    -loop number设置播放循环次数<br/>
    -showmode mode 设置显示模式，可用的模式值:0显示视频1 显示音频波形，2 显示音频频谱。缺省为0，如果视频不存在则自动选择2<br/>
    -vf filtergraph 设置视频滤镜<br/>
    -af filtergraph 设置音频滤镜<br/>
    -stats 打印多个回放统计信息，包括显示流持续时间，编解码器参数流中的当前位置，以及音频/视频同步差值。默认情况下处于启用状态，要显式禁用它则需要指定-nostats<br/>
    -fast 非标准化规范的多媒体兼容<br/>
    -genpts 生成p<br/>
    -sync type 同步类型将主时钟设置为audio (type=audio)，video(type=video)或external (type=ext)，默认是audio为主<br/>
    -ast audio_stream_specifier 指定音频流索引，比如-ast 3，播放流索引为3的<br/>
    -vst video_stream_specifier 指定视频流索引，比如-vst 4，播放流索引为4的<br/>
    -sst subtitle_stream_specifier 指定字幕流索引，比如-sst 5，播放流索引为5的<br/>
    -autoexit 视频播放完毕<br/>
    -exitonkeydown 键盘按下任何键退出播放<br/>
    -exitonmousedown 鼠标按下任何键退出播放<br/>
    -codec:media_specifier codec_namemedia 强制使用设置的多媒体解码器, media_specifier可用值为a(音频)，(视频)和s字幕。比如-codec:v h264_gsv 强制视频采用h264_qsv解码<br/>
    -acodec codec_name 强制使用设置的音频解码器进行音频解码<br/>
    -vcodec codec_name强制使用设置的视频解码器进行视频解码<br/>
    -scodec codec_name强制使用设置的字幕解码器进行字幕解码<br/>
    -autorotate 根据文件元数据自动旋转视频。值为0或1，默认为1<br/>
    -framedrop 如果视频不同步则丢弃视频帧。当主时钟非视频时钟时默认开启。若需禁用则使用 -noframedrop<br/>
    -infbuf 不限制输入缓冲区大小。尽可能快地从输入中读取尽可能多的数据播放实时流时默认启用，如果未及时读取数据，则可能会丢弃数据。此选项将不限制缓冲区的大小。若需禁用则使用-noinfbuf<br/>
 播放本地文件: <br/>
    ffplay -window_title "test time" -ss 2 -t 10 -autoexit test.mp4<br/>
    ffplay buweishui.mp3<br/>
 播放网络流<br/>
    ffplay -window title "rtmp stream'rtmp://202.69.69.180:443/webcast/bshdlive-pc<br/>
 强制解码器<br/>
    mpeg4解码器: ffplay -vcodec mpeg4 test.mp4<br/>
    h264解码器: ffplay -vcodec h264 test.mp4<br/>
 禁用音频或视频:<br/>
    禁用音频: ffplay test.mp4 -an<br/>
    禁用视频: ffplay test.mp4 -vn<br/>
 播放YUV数据: <br/>
    ffplay -pixel_format yuv420p -video_size 320x240 -framerate 5yuv420p_320x240.yuv
 播放RGB数据: <br/>
    ffplay -pixel_format rgb24 -video_size 320x240 -i rgb24_320x240.rgb<br/>
    ffplay -pixel_format rgb24 -video_size 320x240 -framerate 5 -irgb24 320x240.rgb<br/>
 播放PCM数据: <br/>
    ffplay -ar 48000 -ac 2 -ff32le 480002 f32le.pcm<br/>
    -ar set audio sampling rate (in Hz) (from 0 to INT_MAX) (default 0)<br/>
    -ac set number of audio channels (from 0 to INT MAX)(default 0)<br/>
 过滤器: <br/>
    视频旋转: <br/>
      ffplay -i test.mp4 -vftranspose=1<br/>
    视频反转: <br/>
      ffplay test.mp4 -vf hflip<br/>
      ffplay test.mp4 -vf vflip<br/>
    视频旋转和反转: <br/>
      ffplay test.mp4 -vf hflip,transpose=1<br/>
    音频变速播放: <br/>
      ffplay -i test.mp4 -af atempo=2<br/>
    视频变速播放:<br/>
      ffplay -i test.mp4 -vf setpts=PTS/2<br/>
    音视频同时变速: <br/>
      ffplay -i test.mp4 -vf setpts=PTS/2 -af atempo=2<br/>
    更多参考:<br/>
      http://www.ffmpeg.org/ffmpeg-filters.html<br/>
