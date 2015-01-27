#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#include <log4cxx/logger.h>    
#include <log4cxx/logstring.h> 
#include <log4cxx/propertyconfigurator.h> 

#include "ace-radius/Config.h"
#include "ace-radius/RadiusServerStack.h"

#define BUFSIZE 4096
#define PORT 5000

using namespace log4cxx;
LoggerPtr g_logger = Logger::getLogger("RadiusServer");
/*
 * A sample RADIUS server.
 *
 * Usage:
 *     server
 *
 * Notes:
 *   - server listens on authentication port (1812)
 *
 */


//check if user is a bceuser
int VerifyBceUser(char *password, char *username, char *IpStr)
{
    int h, i, length, ret, sockfd;
    struct sockaddr_in servaddr;
    struct timeval  tv;
    char  buf[BUFSIZE], str1[BUFSIZE];	    
    fd_set   t_set1;
    socklen_t len;
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 )
    {
        LOG4CXX_ERROR(g_logger, "create network connections failure---socket error!");
        return -1;
    }

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    if (inet_pton(AF_INET, IpStr, &servaddr.sin_addr) <= 0 )
    {
        LOG4CXX_ERROR(g_logger, "create network connections failure--inet_pton error!");
        return -1;
    }

    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        LOG4CXX_ERROR(g_logger, "connect to server failure,connect error!");
        return -1;
    }
    LOG4CXX_DEBUG(g_logger, "connect success");
    memset(str1, 0, BUFSIZE);
    length = snprintf(str1, sizeof(str1), "HEAD /v2.0/tokens/%s?tenant_id=%s HTTP/1.1\r\n\r\n", password, username);
    if (length > BUFSIZE)
    {
        LOG4CXX_ERROR(g_logger, "buffer overflow!");
        return -1;
    }
    ret = write(sockfd,str1,strlen(str1));
    if (ret < 0)
    {
        LOG4CXX_ERROR(g_logger, "send failure");
        return -1;
    }
    else
    {
        LOG4CXX_DEBUG(g_logger, "send message success!");
    }

    FD_ZERO(&t_set1);
    FD_SET(sockfd, &t_set1);

    while(1)
    {
        sleep(2);
        tv.tv_sec= 0;
        tv.tv_usec= 0;
        h= 0;
        h= select(sockfd +1, &t_set1, NULL, NULL, &tv);
        if (h < 0)
        {
            close(sockfd);
            LOG4CXX_ERROR(g_logger, "no that user in bce!");
            return -1;
        }
        if (h > 0)
        {
            memset(buf, 0, 4096);
            i= read(sockfd, buf, 4095);
            if (i==0)
            {
                close(sockfd);
            }
	    std::string logstr(buf);
            LOG4CXX_DEBUG(g_logger, logstr.c_str());
            char str1[20] = "HTTP/1.1";
            char *s;
            if (buf != NULL)
                s = strstr(buf, (char *)str1);
            if (s != NULL && strlen(s) > 0)
            {
                char str2[20] = "HTTP/1.1 204";
                s = strstr(buf, (char *)str2);
                if (s != NULL && strlen(s)>0)
                {
                    LOG4CXX_DEBUG(g_logger, "VerifyBceUser accept");
                    return 1;
                }
                else
                {
                    LOG4CXX_DEBUG(g_logger, "VerifyBceUser fail!");
                    return 0;
                }
            }
        }
      }
      close(sockfd);
      LOG4CXX_DEBUG(g_logger, "VerifyBceUser  fail!");
      return 0;
}

int verifyRequest(RadiusPacket & p_request, char * IpStr)
{
    RadiusAttribute l_attr;
    const char *l_data;
    char *username;
    char *password;
    uint16_t l_length;
    char l_password[D_USER_PASSWORD_MAX_LENGTH];

    // answer only ACCESS_REQUEST packets
    if (p_request.getCode() != D_PACKET_ACCESS_REQUEST)
    {
        LOG4CXX_ERROR(g_logger, "Wrong request code");
        return RC_FAIL;
    }

    // verify User-Name attribute
    if (p_request.findAttribute(D_ATTR_USER_NAME, l_attr) != RC_SUCCESS)
    {
        LOG4CXX_ERROR(g_logger, "Can't find User-Name attribute");
        return RC_FAIL;
    }

    if (l_attr.getString(l_data, l_length) != RC_SUCCESS)
    {
        LOG4CXX_ERROR(g_logger, "Can't parse User-Name attribute");
        return RC_FAIL;
    }
    username = (char *)malloc(l_length+1);
    if(l_data != NULL)
        memcpy(username, l_data, l_length);
    username[l_length]='\0';
    // verify User-Password attribute
    if (p_request.findAttribute(D_ATTR_USER_PASSWORD, l_attr) != RC_SUCCESS)
    {
        LOG4CXX_ERROR(g_logger, "Can't find User-Password attribute");
        return RC_FAIL;
    }

    if (l_attr.getUserPassword(l_password, l_length) != RC_SUCCESS)
    {
        LOG4CXX_ERROR(g_logger, "Can't parse User-Password attribute");
        return RC_FAIL;
    }
    password = (char *)malloc(l_length+1);
    if (l_password != NULL)
        memcpy(password, l_password, l_length);
    password[l_length]='\0';
    std::ostringstream oss;
    oss << "username = " << username << " passpword=" << password;
    LOG4CXX_DEBUG(g_logger, oss.str().c_str());
    if (VerifyBceUser(password, username, IpStr) != 1)
    {
        return RC_FAIL;
    }
    // everything looks OK
    free (username);
    free (password);
    return RC_SUCCESS;
}


int sendResponse(RadiusServerStack &p_stack, unsigned char str,
		const char *host_ip_address)
{
    // ----------------------
    // build response packet
    // ----------------------
    RadiusPacket l_response(str, p_stack.getRequest());
    RadiusAttribute l_attr;

    // add Service-Type attribute
    l_response.addAttribute(D_ATTR_SERVICE_TYPE, l_attr);
    l_attr.setNumber(1);

    // add Login-Service attribute
    l_response.addAttribute(D_ATTR_LOGIN_SERVICE, l_attr);
    l_attr.setNumber(0);

    // add Login-IP-Host attribute
    l_response.addAttribute(D_ATTR_LOGIN_IP_HOST, l_attr);
    struct in_addr l_addr;
    inet_aton(host_ip_address, &l_addr);
    l_attr.setIPAddress(l_addr);

    // ----------------------
    // send response packet
    // ----------------------
    p_stack.sendResponse(l_response);
    char str1[2000];
    memset(str1, 0, sizeof(str1));
    LOG4CXX_DEBUG(g_logger, "response packet:");
    LOG4CXX_DEBUG(g_logger, l_response.dump(str1));
    return RC_SUCCESS;
}

int main (int argc, char *argv[])
{
    signal(SIGPIPE, SIG_IGN);
    // 读取配置文件 
    PropertyConfigurator::configure("ServerLogConfig.data");
    //LOG4CXX_TRACE(g_logger, "跟踪");
    // LOG4CXX_WARN(g_logger, "警告");
    //LOG4CXX_DEBUG(g_logger, "调试");
    //LOG4CXX_ASSERT(g_logger, false, "断言");
    // LOG4CXX_FATAL(g_logger, "致命");
    int l_rc, i;
    char str[4096];
    char str1[1000];
    std::string ip_address;
    std::string host_ip_address;
    const char ConfigFile[] = "RadiusConfig.data";
    Config configSettings(ConfigFile);
    ip_address = configSettings.Read("BceIpAddress", ip_address);
    host_ip_address = configSettings.Read("ServerHostIpAddress", host_ip_address);
    char IpStr[20];
    memset(IpStr, 0, sizeof(IpStr));
    for(i=0; ip_address[i] != '\0'; i++)
        IpStr[i] = ip_address[i];
    IpStr[i] = '\0';
    char Host_ip_address[20];
    memset(Host_ip_address, 0, sizeof(Host_ip_address));
    for(i=0; host_ip_address[i] != '\0'; i++)
        Host_ip_address[i] = host_ip_address[i];
    Host_ip_address[i] = '\0';
    memset(str, 0, sizeof(str));
    // create instance of server stack
    RadiusServerStack l_stack(RadiusSecret("qyzzy7561"));
    if (!l_stack.isValid())
    {
        LOG4CXX_ERROR(g_logger, "Can not create RADIUS server stack");
        return 1;
    }

    // reference to request packet
    RadiusPacket & l_request = l_stack.getRequest();

    while (1)
    {
        l_rc = l_stack.receiveRequest();
        if (l_rc == RC_SUCCESS)
        {
            LOG4CXX_DEBUG(g_logger, "*********Verify start**********");
	    LOG4CXX_DEBUG(g_logger, "receive request from ip ");
            LOG4CXX_DEBUG(g_logger, l_stack.getClientAddress().dump(str));
	    memset(str, 0, sizeof(str));
	    LOG4CXX_DEBUG(g_logger, "request packet:   ");
            LOG4CXX_DEBUG(g_logger, l_request.dump(str));
            if (verifyRequest(l_stack.getRequest(), IpStr) == RC_SUCCESS)
            {

                LOG4CXX_DEBUG(g_logger, "Verify         OK");
                sendResponse(l_stack, D_PACKET_ACCESS_ACCEPT, Host_ip_address);
            }
            else
            {
                LOG4CXX_DEBUG(g_logger, "Verify         NO");
                sendResponse(l_stack, D_PACKET_ACCESS_REJECT, Host_ip_address);
            }
            LOG4CXX_DEBUG(g_logger, "*******Verify end****************");
        }
        else
            LOG4CXX_ERROR(g_logger, "Error 1");
    }
    return 0;
}
