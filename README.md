# eyescan
## ファイルの依存関係
```
eyescan.cpp：GUIを立ち上げる
　└GUIWindow.cpp：GUIのウィンドウに必要な枠を生成する
　　　└GroupBox：GUIの枠に必要なボタンやキャンバスを配置する
　　　　　├ClickPos.cp：マウスでキャンバスをクリックした時に座標を取得する
　　　　　└decode.cp：キャンバスにrootファイルにある飛跡データを表示できるようにする
```

## rootファイルに保存しておくべき飛跡データの形式
rootファイルにそのままmapを保存してしまうと，
無駄にファイルサイズを大きくしてしまうのでencodeしておく．
encodeのルールとしてはunsigned long 型の変数にmapの0, 1を詰めていく．
raw[2][1024][256]のmapをencodeするルーチンは以下の通り
"Map"というブランチ名でtreeに詰めておく．

```
for(int ii=0;ii!=2;++ii){
  for(int jj=0;jj!=1024;++jj){
    for(int kk=0;kk!=256;++kk){
      if(raw[ii][jj][kk]!=0){
        Map[ii][kk][jj/32] += (((UInt_t)1)<<(k%32));
      }
    }
  }
}
```

## eyescanの進め方
1. "User" のプルダウンから自分の名前を選択し，"Login" ボタンを押す．
（登録されていないときは右の欄に入力し"Add user" ボタンを押す）
2. "Run#" のプルダウンからeyescan をするラン番号を選択する．
3. "Start" ボタンを押して解析を始める．
4. キャンバスに表示されている飛跡の本数を"Track Number" のラジオボタンから選択し，"Select" ボタンを押す．
5. "Anode" または"Cathode" ボタンを押し，飛跡の抽出モードに移行する．（押した方の画像が拡大される）
6. 飛跡が集まっている点をクリックする．
7. 各荷電粒子が停止した点をクリックする．（anode およびcathode で飛跡の順番が対応するように選択する）
8. anode とcathode の両方でTrack Number + 1 この点を選択したら，"Next" ボタンを押す．
9. 4 に戻り次のイベントの解析を行う．

何か間違った操作を行った場合は"Cancel" ボタンを押すことで，
そのイベントにおける操作を全てキャンセルする．
"Stop" ボタンを押すことで"Run #"のプルダウンが復活し，別のランを選択することができるようになる．
途中でやめても，そのイベントから再開できるので疲れたら休憩してください．
それぞれのボタンはAlt + 頭文字でショートカットできる．

## eyescanの解析結果の出力形式
各イベント毎に"RunNo EventNo EventId ax0 ay0 cx0 cy0 ax1 ay1 cx1 cy1 ax2 ay2 cx2 cy2 ax3 ay3 cx3 cy3"の順でテキストファイルに出力．
### 各変数の意味
- RunNo: 解析したランの番号
- EventNo: 解析したイベントの番号
- EvnetId: 解析したイベントの飛跡の本数
- ax--cy: 0は散乱点，1--3は停止した点．x座標はストリップ番号，y座標はクロック番号．
  - ax: anode のx 座標
  - ay: anode のy 座標
  - cx: cathode のx 座標
  - cy: cathode のy 座標