// Author: zhengsh
// Date: 2005/10/05 15:48:42
// $Id: Constant.h,v 1.27 2006/09/29 15:31:33 zhengsh Exp $

#ifndef CONFIGURE_H
#define CONFIGURE_H
#include "vcl.h"

const AnsiString DIR_PROJECT = "\\Project\\";
//����Ŀ¼
const AnsiString DIR_IMAGES = "\\Images\\";
//ͼ��Ŀ¼
const AnsiString DIR_BIN = "\\Bin\\";
//��ִ���ļ�Ŀ¼
const AnsiString DIR_LANG = "\\Lang\\";
//���԰�
const AnsiString DIR_CONF = "\\Config\\";
//
const AnsiString DIR_CACHE = "\\Cache\\";
// cache dir
const AnsiString DIR_SAVE = "\\Save\\";
// user dir to save file
const AnsiString DIR_DOCS = "\\Docs\\";
//Skins
const AnsiString DIR_SKINS = "\\Skins\\";

const AnsiString SYSTEM_CONFIG_FILE = "config.ini";
//extension of skin file
const AnsiString EXT_SKIN = ".sui";
//extension of language file
const AnsiString EXT_LANG = ".lang";


//�����ļ�
const int DEFAULT_PORT = 9999;
//Ĭ�ϵĶ˿ں�
const AnsiString FILE_CACHE = "Buffer";
const AnsiString DEFUALT_LANGUAGE = "English";

const int BUFFER_SIZE = 1600;
//�������ݰ��Ļ�������С

const int ICMP_HEADER_SIZE = 4;
//ICMP����ͷ����
const int UDP_HEADER_SIZE = 8;
//UDP��ͷ����
const int TCP_HEADER_SIZE = 20;
//TCP��ͷ����
const int DATA_SHOW_LEN=25;

//Options source
const int OPTION_SOURCE_ALL = 1;
const int OPTION_SOURCE_ONLY = 2;
const int OPTION_SOURCE_SEGMENT = 3;

//Options DESTINE
const int OPTION_DESTINE_ALL = 1;
const int OPTION_DESTINE_ONLY = 2;
const int OPTION_DESTINE_SEGMENT = 3;

const AnsiString SECTION_OPTOINS = "Options";
const int ETHERNET_TYPE_IP = 0x0800;
//IP ���ݱ�
const int ETHERNET_TYPE_ARP = 0x0806;
//ARP
const int ETHERNET_TYPE_RARP = 0x0835;
//RARP

const AnsiString FILE_ICON_UP = "up16.ico";
//up icons
const AnsiString FILE_ICON_DOWN = "down16.ico";
//down icons

const int DEFAULT_RECORD_COUNT_PERPAGE = 1000;
//image files
const AnsiString FILE_ACTIVE = "active.ico";
const AnsiString FILE_INACTIVE = "inactive.ico";
const AnsiString FILE_HELP = "note.chm";
const AnsiString FILE_TUTORIAL = "tutorial.chm";
const AnsiString MAIL_FEEDBACK = "shaohui_1983@163.com";
const AnsiString FILE_AUTOSAVE = "autosave.sni";
const AnsiString FILE_WINPCAP = "WinPcap_3_1.exe";

const AnsiString URL_SOURCE_CODE = "http://blog.csdn.net/shaohui";

const int NUMBER_MAX_SPECIFY_PORT = 100;
//the maximum port number what user can specify

const int SPLASH_TIME = 500;
const AnsiString SOFTWARE_TITLE_CAPTION = "[SnifferFox]";
//const AnsiString SOFTWARE_NAME = "SnifferFox";

// message type, if type varies, the icon with varies
const int MSG_HELP      = 0;
const int MSG_INFO      = 1;
const int MSG_STOP      = 2;
const int MSG_ERROR     = 2;
const int MSG_WARNING   = 3;
const int MSG_NONE      = 5;

//const int LENGTH_MSG_BOX = 35;

#endif





