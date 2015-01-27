/*
 * This source file is part of the ace-radius library.  This code was
 * written by Alex Agranov in 2004-2009, and is covered by the BSD open source
 * license. Refer to the accompanying documentation for details on usage and
 * license.
 */

#include <stdio.h>
#include <string.h>
#include <signal.h>

#include "log4cxx/logger.h"
#include "log4cxx/logstring.h"
#include "log4cxx/propertyconfigurator.h"

#include "ace-radius/Config.h"
#include "ace-radius/RadiusClientStack.h"

/*
 * A sample RADIUS client. 
 *  
 * Usage: 
 *     client [server-ip]
 *  
 * Notes: 
 *    - if server-ip is not specified, "localhost" is user instead
 *    - client sends Access-Request packet to authentication port (1812)
 *      with username and password you set in RadiusConfig.data
 *    - response packet is dumped (if received)
 */

using namespace log4cxx;
LoggerPtr g_logger = Logger::getLogger("RadiusClient");

int main(int argc, char *argv[])
{
    signal(SIGPIPE, SIG_IGN);
    PropertyConfigurator::configure("ClientLogConfig.data");
    int i;
    std::string username;
    std::string password;
    std::string client_host_ip;
    const char ConfigFile[] = "RadiusConfig.data";
    Config configSettings(ConfigFile);
    username = configSettings.Read("username", username);
    password = configSettings.Read("password", password);
    char Username[100], Password[100], Client_host_ip[20];
    for(i=0; username[i]!='\0'; i++)
        Username[i] = username[i];
    Username[i] = '\0';
    for(i=0; password[i]!='\0'; i++)
	Password[i] = password[i];
    Password[i] = '\0';
    for(i=0; client_host_ip[i]!='\0'; i++)
	Client_host_ip[i] = client_host_ip[i];
    Client_host_ip[i] = '\0';
    LOG4CXX_DEBUG(g_logger, "user test strat");

    LOG4CXX_DEBUG(g_logger, "Test RADIUS Client application");
    
    // create instance of client stack
    RadiusClientStack l_stack;
    if (!l_stack.isValid())
    {
        LOG4CXX_DEBUG(g_logger, "Can not create RADIUS client stack");
        return 1;
    }

    //add connection with some RADIUS server
    if (argc >= 2)
        l_stack.addServer(argv[1], D_RADIUS_AUTHENTICATION_PORT, RadiusSecret("qyzzy7561"));
    else
    l_stack.addServer("localhost", D_RADIUS_AUTHENTICATION_PORT, RadiusSecret("qyzzy7561"));
    
    // create a new packet
    RadiusPacket l_packet(D_PACKET_ACCESS_REQUEST, l_stack);
    
    // add some attributes to the packet
    RadiusAttribute l_attr;
    
    l_packet.addAttribute(D_ATTR_USER_NAME, l_attr);
    l_attr.setString(Username);

    l_packet.addAttribute(D_ATTR_USER_PASSWORD, l_attr);
    l_attr.setUserPassword(Password);

    struct in_addr l_addr;
    inet_aton((const char *)Client_host_ip, &l_addr);
    l_packet.addAttribute(D_ATTR_NAS_IP_ADDRESS, l_attr);
    l_attr.setIPAddress(l_addr);
    l_packet.addAttribute(D_ATTR_NAS_PORT, l_attr);
    l_attr.setNumber(3);

    char str[2000];
    memset(str, 0, sizeof(str));
    LOG4CXX_DEBUG(g_logger, "the send packet :");
    LOG4CXX_DEBUG(g_logger, l_packet.dump(str));
    // send the packet
    RadiusPacket * l_response = l_stack.sendPacket(l_packet);

    // print response if it was received
    if (l_response)
    {
        LOG4CXX_DEBUG(g_logger, "---Packet was successfully transmitted---");
	memset(str, 0, sizeof(str));
	LOG4CXX_DEBUG(g_logger, l_response->dump(str));
        if(strcmp(l_response->getCodeDescription(), "Access-Accept") == 0) 
        {
            LOG4CXX_DEBUG(g_logger, "user test---OK---"); 
	}
	else
        {
	    LOG4CXX_DEBUG(g_logger, "user test---NO---"); 
	}
        //printf("%s\n", l_response->getCode());
        //if (strcmp(l_response->getCode() ,"D_PACKET_ACCESS_ACCEPT") == 0)
        //   return 0;
        // l_response->dump();
    }
    else
        LOG4CXX_DEBUG(g_logger, "---Packet transmit failure---"); 
    return 0;
}
