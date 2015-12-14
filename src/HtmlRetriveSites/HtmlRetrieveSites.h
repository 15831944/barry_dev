//////////////////////////////////////////////////////////////////////////////////
//
//	Copyright (C) 2011
//
//	Define html compiler util
//	create by Ken Lee 2011/04/11
///////////////////////////////////////////////////////////////////////////////////
#ifndef Aos_HtmlServer_HtmlRetrieveSites_h
#define Aos_HtmlServer_HtmlRetrieveSites_h

#include "Util/RCObject.h"
#include "Util/String.h"
#include "HtmlServer/HtmlReqProc.h"
#include "XmlUtil/XmlTag.h"
#include "SEUtil/DocTags.h"
#include <vector>

class AosHtmlRetrieveSites
{
	private:
		//site editor
		int         mPageNumber;
		std::vector<OmnString>  mVpdArray;
		std::vector<OmnString>  mVpdnamelist;
		std::vector<OmnString>  msVpdname;
	
	public:
		AosHtmlRetrieveSites();
		~AosHtmlRetrieveSites();

		bool retrieveAllSites(
			OmnString &xmlStr,
			const AosXmlTagPtr &cookies,
			const OmnString &mSiteid,
			const OmnString &sessionId,
			const OmnString &isInEditor,
			const OmnString &vpdname,
			OmnString &errmsg);

		bool retrieveSites(
			const AosXmlTagPtr &vpd,
			OmnString &errmsg,
			const OmnString &superVpdname);

		bool procCompoundPane(
			const AosXmlTagPtr &compoundPane,
			const OmnString &superVpdname);

		bool procPane(
			const AosXmlTagPtr &pane,
			const OmnString &superVpdname);

		bool procPanel(
			const AosXmlTagPtr &panel,
			const OmnString &superVpdname);

		bool procGic(
			const AosXmlTagPtr &gic_creators,
			const OmnString &gic_type,
			const OmnString &superVpdname);

		bool procAction(
			const AosXmlTagPtr &action,
			const OmnString &gic_type,
			const OmnString &superVpdname);

		bool convertToXml(
			const std::vector<OmnString> &mVpdnamelist,
			OmnString &namelist,
			OmnString &errmsg);
};
#endif