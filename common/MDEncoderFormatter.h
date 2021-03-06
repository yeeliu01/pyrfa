#ifndef __SESSION_LAYER_THREADED_EXAMPLE__MDENCODERFORMATTER__H__
#define __SESSION_LAYER_THREADED_EXAMPLE__MDENCODERFORMATTER__H__

#include "SessionLayer/MarketDataEnums.h"
#include "Common/RFA_String.h"
#include "Common/Buffer.h"

#include <stdlib.h>
#include <list>

// Tib Msg library
#include "TibMsg.h"

//AnsiPage library
#include "Page.h"

#define MAX_PAGEBUFFER	512
#define MAX_UPDATES		1000
#if defined (WIN32)
	#define SNPRINTF _snprintf
#else
	#define SNPRINTF snprintf
#endif

//Windows doesn't have any Reentrant functions
//Define for using the same format on Linux and Solaris
#if defined (WIN32)
#define rand_r(a)			rand()
#endif

using namespace rfa::common;
using namespace rfa::sessionLayer;
using namespace std;
using namespace rfa::AnsiPage;

class CMFEncoder;
class CMDEncoderFormatter
{
public:
	CMDEncoderFormatter();
	~CMDEncoderFormatter();
	
	typedef list<RFA_String>	FieldList;

	//Set data format for message
	void setDataFormat(MarketDataEnums::DataFormat dataFormat);
	//Get data format of message
	const MarketDataEnums::DataFormat getDataFormat() const;
	//Clear buffer
	void clearBuffer();

	/*** These functions are to format market data in Marketfeed ***/
	
	//Initial marketfeed encoder
	void initializeMarketfeedData();
	//Get marketfeed buffer as string
	const char * getMarketfeedDataBuffer() const;
	
	//Make multiple marketfeed fields by passing a list of field ID and an integer to generate random data
	void makeMarketfeedFields(FieldList fidList, unsigned int uiRand);
	//Make a marketfeed field by passing a field ID and a value
	void makeMarketfeedField(const RFA_String &fid,const RFA_String &value);
	
	//Format image marketfeed as RFA buffer
	Buffer FormatMarketfeedImageBuffer(const RFA_String & ricName);
	//Format update marketfeed as RFA buffer
	Buffer FormatMarketfeedUpdateBuffer(const RFA_String & ricName);
	
	/*** End of marketfeed formatting ***/

	/*** Thses functions are to format market data in TibMsg ***/
	
	//Initial TibMsg
	void initializeTibMsg(char * buffer, int size);
	//Get TibMsg
	const TibMsg & getTibMsg();
	
	//Make muliple TibMsg fields by passing a list of field name and an integer to generate random data
	void makeTibFields(FieldList fidList, unsigned int uiRand);
	//Make a TibMsg field by passing a field name and any TibMsg type of value. In case passing string as value, size value must not be set.
	void makeTibField(const RFA_String &fid, const void * value, TibMsg_type type = TIBMSG_NODATA, int size = 0);

	//Format TibMsg as RFA buffer
	Buffer FormatTibMsgDataBuffer();
	
	/* End of TibMsg formatting */

	/*** These functions are to format market data in AnsiPage ***/

	//Initial PageCell
	void initializePageCell(char cChar,
				PageCell::GraphicSet graphicSet,
				PageCell::CellStyle style,
				PageCell::CellStyle fadeStyle,
				PageCell::CellColor foregroundColor,
				PageCell::CellColor backgroundColor,
				PageCell::CellColor foregroundFadeColor,
				PageCell::CellColor backgroundFadeColor);
	//Get Page
	const Page & getAnsiPage();

	//Make a Page
	void makePageCells(const char* value, short beginningRow, short beginningColumn);
	
	//Format AnsiPage as RFA buffer
	Buffer FormatAnsiPageDataBuffer();

	/*** End of AnsiPage formatting ***/

private:
	MarketDataEnums::DataFormat _dataFormat;
	CMFEncoder	*		_mfEncoder;
	TibMsg				_tibMsg; 
	PageCell			_modelCell;
	Page				_page;
	char				_strUpdatePageBuff[MAX_PAGEBUFFER];
	//This array will be used to hold a list of update pages
	PageUpdate			_updateList[MAX_UPDATES];

private:
	// Declared, but not implemented to prevent default behavior generated by compiler
	CMDEncoderFormatter( const CMDEncoderFormatter & );
	CMDEncoderFormatter & operator=( const CMDEncoderFormatter & );
};

#endif // __SESSION_LAYER_THREADED_EXAMPLE__MDENCODERFORMATTER__H__

