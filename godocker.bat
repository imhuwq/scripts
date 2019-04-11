set action=%1
echo "172.129.2.2:22"

if "%action%"=="enter" ( docker exec -it scripts-dev /bin/bash )
else if "%action%"=="build" ( docker-compose build )
else if "%action%"=="up" ( docker-compose up -d )
else if "%action%"=="down" ( docker-compose down )
