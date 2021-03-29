### page
+ 主页
  + 获取主页显示的回答列表
    + api/getList
+ 问题
  + /question
    + qid = int
    + aid = int
      + 指定显示单个回答
  + api/question
  + api/answer
  + 图片
  + markdown
+ 个人主页
  + /user
    + uid = int
  + api/user

### 功能
+ 注册
+ 发起问题
+ 修改问题
+ 搜索
+ 私信
+ 推送
+ 关注问题

### api
+ api/getList
  + offset = 0
+ api/question_info
  + qid
+ api/question_answer
  + qid
  + offset = 0
+ api/answer
  + aid
+ api/user
  + uid 缺省为自己

### typing
+ question
  + qid
  + title
  + description
+ answer
  + aid
  + qid
  + user
  + text
  ~~+ comment~~
  + vote
    + voteup
    + votedown
    + isvote
  + time 
    + create time
    + edited time
+ user
  + uid
  + name
  + mail
  + gender
    + female male unknown
  + avatar
    + url 外链图床
  + description