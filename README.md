# SSAD homework
software system analysis and design 基于问答的讨论社区

# 安装配置
项目分为两部分:静态页面与api。api使用uvicorn运行在网站目录 `/api` 下，
## 参考配置过程
1. 下载或者 clone 本库
2. 安装配置 python api
   1. python3.8 及以上
   2. `python3.8 -m pip install -r requirement.txt`
   3. `python3.8 -m api` 运行api模块
   4. 此时api已经运行在 `127.0.0.1:8081`
3. 配置web服务器
   1. 参考nginx配置文档
        ```
        server{
            listen 80;
            
            # ip or domain
            server_name localhost;

            root /path/to/page/;
            index index.html;
            
            location /api/ {
                proxy_pass http://127.0.0.1:8081/;
            }
        }
        ```