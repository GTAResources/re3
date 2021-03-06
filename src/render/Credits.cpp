#include "common.h"
#include "patcher.h"
#include "Timer.h"
#include "Font.h"
#include "Frontend.h"
#include "RwHelper.h"
#include "Camera.h"
#include "Text.h"
#include "Credits.h"

bool &CCredits::bCreditsGoing = *(bool*)0x95CDD3;
uint32 &CCredits::CreditsStartTime = *(uint32*)0x8F2528;

void
CCredits::Init(void)
{
	Stop();
}

void
CCredits::Start(void)
{
	bCreditsGoing = true;
	CreditsStartTime = CTimer::GetTimeInMilliseconds();
}

void
CCredits::Stop(void)
{
	bCreditsGoing = false;
}

void
CCredits::PrintCreditSpace(float space, uint32 &line)
{
	line += space * 25.0f;
}

void
CCredits::PrintCreditText(float scaleX, float scaleY, wchar *text, uint32 &lineoffset, float scrolloffset)
{
	float start = SCREEN_HEIGHT + 50.0f;
	float y = lineoffset + start - scrolloffset;
	if(y > -50.0f && y < start){
		CFont::SetScale(scaleX, scaleY);
		CFont::PrintString(SCREEN_WIDTH/2.0f, y, (uint16*)text);
	}
	lineoffset += scaleY*25.0f;
}

void
CCredits::Render(void)
{
	uint32 lineoffset;
	float scrolloffset;

	if(!bCreditsGoing || FrontEndMenuManager.m_bMenuActive)
		return;

	DefinedState();
	lineoffset = 0;
	scrolloffset = (CTimer::GetTimeInMilliseconds() - CreditsStartTime) / 24.0f;
	CFont::SetJustifyOff();
	CFont::SetBackgroundOff();
	CFont::SetCentreSize(SCREEN_WIDTH - 20);
	CFont::SetCentreOn();
	CFont::SetPropOn();
	CFont::SetColor(CRGBA(220, 220, 220, 220));
	CFont::SetFontStyle(FONT_HEADING);

	PrintCreditSpace(2.0, lineoffset);
	PrintCreditText(1.7, 1.0, TheText.Get("CRED002"), lineoffset, scrolloffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRED003"), lineoffset, scrolloffset);
	PrintCreditSpace(2.0, lineoffset);
	PrintCreditText(1.7, 1.0, TheText.Get("CRED004"), lineoffset, scrolloffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRED005"), lineoffset, scrolloffset);
	PrintCreditSpace(2.0, lineoffset);
	PrintCreditText(1.7, 1.0, TheText.Get("CRED006"), lineoffset, scrolloffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRED007"), lineoffset, scrolloffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRED008"), lineoffset, scrolloffset);
	PrintCreditSpace(2.0, lineoffset);
	PrintCreditSpace(2.0, lineoffset);
	PrintCreditText(1.7, 1.0, TheText.Get("CRED009"), lineoffset, scrolloffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRED010"), lineoffset, scrolloffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRED011"), lineoffset, scrolloffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRED012"), lineoffset, scrolloffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRED013"), lineoffset, scrolloffset);
	PrintCreditSpace(2.0, lineoffset);
	PrintCreditText(1.7, 1.0, TheText.Get("CRED014"), lineoffset, scrolloffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRED015"), lineoffset, scrolloffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRED016"), lineoffset, scrolloffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRED017"), lineoffset, scrolloffset);
	PrintCreditSpace(2.0, lineoffset);
	PrintCreditSpace(2.0, lineoffset);
	PrintCreditText(1.7, 1.0, TheText.Get("CRED018"), lineoffset, scrolloffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRED019"), lineoffset, scrolloffset);
	PrintCreditSpace(2.0, lineoffset);
	PrintCreditText(1.4, 0.82, TheText.Get("CRED020"), lineoffset, scrolloffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRED021"), lineoffset, scrolloffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRED022"), lineoffset, scrolloffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRED245"), lineoffset, scrolloffset);
	PrintCreditSpace(2.0, lineoffset);
	PrintCreditText(1.7, 1.0, TheText.Get("CRED023"), lineoffset, scrolloffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRED024"), lineoffset, scrolloffset);
	PrintCreditSpace(2.0, lineoffset);
	PrintCreditText(1.7, 1.0, TheText.Get("CRED025"), lineoffset, scrolloffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRED026"), lineoffset, scrolloffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRED027"), lineoffset, scrolloffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRED028"), lineoffset, scrolloffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRED257"), lineoffset, scrolloffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRED029"), lineoffset, scrolloffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRED030"), lineoffset, scrolloffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRED031"), lineoffset, scrolloffset);
	PrintCreditSpace(2.0, lineoffset);
	PrintCreditSpace(2.0, lineoffset);
	PrintCreditText(1.7, 1.0, TheText.Get("CRED032"), lineoffset, scrolloffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRED033"), lineoffset, scrolloffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRED244"), lineoffset, scrolloffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRED034"), lineoffset, scrolloffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRED035"), lineoffset, scrolloffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRED247"), lineoffset, scrolloffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRED036"), lineoffset, scrolloffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRED037"), lineoffset, scrolloffset);
	PrintCreditSpace(2.0, lineoffset);
	PrintCreditSpace(2.0, lineoffset);
	PrintCreditText(1.7, 1.0, TheText.Get("CRED038"), lineoffset, scrolloffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRED039"), lineoffset, scrolloffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRED040"), lineoffset, scrolloffset);
	PrintCreditSpace(2.0, lineoffset);
	PrintCreditText(1.4, 0.82, TheText.Get("CRED041"), lineoffset, scrolloffset);
	if(CMenuManager::m_PrefsLanguage == LANGUAGE_ITALIAN)
	        PrintCreditSpace(1.5, lineoffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRED042"), lineoffset, scrolloffset);
	PrintCreditSpace(2.0, lineoffset);
	PrintCreditText(1.7, 1.0, TheText.Get("CRED043"), lineoffset, scrolloffset);
	if(CMenuManager::m_PrefsLanguage == LANGUAGE_ITALIAN)
	        PrintCreditSpace(1.5, lineoffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRED044"), lineoffset, scrolloffset);
	PrintCreditSpace(2.0, lineoffset);
	PrintCreditSpace(2.0, lineoffset);
	PrintCreditText(1.7, 1.0, TheText.Get("CRED045"), lineoffset, scrolloffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRED046"), lineoffset, scrolloffset);
	PrintCreditSpace(2.0, lineoffset);
	PrintCreditText(1.7, 1.0, TheText.Get("CRED047"), lineoffset, scrolloffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRED048"), lineoffset, scrolloffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRED049"), lineoffset, scrolloffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRED050"), lineoffset, scrolloffset);
	PrintCreditSpace(2.0, lineoffset);
	PrintCreditText(1.7, 1.0, TheText.Get("CRD050A"), lineoffset, scrolloffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRED051"), lineoffset, scrolloffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRED052"), lineoffset, scrolloffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRED053"), lineoffset, scrolloffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRED054"), lineoffset, scrolloffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRED055"), lineoffset, scrolloffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRED056"), lineoffset, scrolloffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRED248"), lineoffset, scrolloffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRED249"), lineoffset, scrolloffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRED250"), lineoffset, scrolloffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRED251"), lineoffset, scrolloffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRED252"), lineoffset, scrolloffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRED253"), lineoffset, scrolloffset);
	PrintCreditSpace(2.0, lineoffset);
	PrintCreditSpace(2.0, lineoffset);
	PrintCreditText(1.7, 1.0, TheText.Get("CRED057"), lineoffset, scrolloffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRED058"), lineoffset, scrolloffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRED059"), lineoffset, scrolloffset);
	PrintCreditSpace(2.0, lineoffset);
	PrintCreditSpace(2.0, lineoffset);
	PrintCreditText(1.7, 1.0, TheText.Get("CRED254"), lineoffset, scrolloffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRED255"), lineoffset, scrolloffset);
	PrintCreditSpace(2.0, lineoffset);
	PrintCreditSpace(2.0, lineoffset);
	PrintCreditSpace(2.0, lineoffset);
	PrintCreditSpace(2.0, lineoffset);
	PrintCreditText(1.7, 1.0, TheText.Get("CRED060"), lineoffset, scrolloffset);
	PrintCreditSpace(2.0, lineoffset);
	PrintCreditSpace(2.0, lineoffset);
	PrintCreditText(1.7, 1.0, TheText.Get("CRED061"), lineoffset, scrolloffset);
	if(CMenuManager::m_PrefsLanguage == LANGUAGE_ITALIAN)
	        PrintCreditSpace(1.5, lineoffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRED062"), lineoffset, scrolloffset);
	PrintCreditSpace(2.0, lineoffset);
	PrintCreditText(1.7, 1.0, TheText.Get("CRED063"), lineoffset, scrolloffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRED064"), lineoffset, scrolloffset);
	PrintCreditSpace(2.0, lineoffset);
	PrintCreditText(1.7, 1.0, TheText.Get("CRED065"), lineoffset, scrolloffset);
	PrintCreditSpace(1.5, lineoffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRED066"), lineoffset, scrolloffset);
	PrintCreditSpace(2.0, lineoffset);
	PrintCreditText(1.7, 1.0, TheText.Get("CRED067"), lineoffset, scrolloffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRED068"), lineoffset, scrolloffset);
	PrintCreditSpace(2.0, lineoffset);
	PrintCreditText(1.7, 1.0, TheText.Get("CRED069"), lineoffset, scrolloffset);
	if(CMenuManager::m_PrefsLanguage == LANGUAGE_ITALIAN)
	        PrintCreditSpace(1.5, lineoffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRED070"), lineoffset, scrolloffset);
	PrintCreditSpace(2.0, lineoffset);
	PrintCreditText(1.7, 1.0, TheText.Get("CRED071"), lineoffset, scrolloffset);
	PrintCreditSpace(1.5, lineoffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRED072"), lineoffset, scrolloffset);
	PrintCreditSpace(2.0, lineoffset);
	PrintCreditSpace(2.0, lineoffset);
	PrintCreditText(1.7, 1.0, TheText.Get("CRED073"), lineoffset, scrolloffset);
	PrintCreditSpace(1.5, lineoffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRED074"), lineoffset, scrolloffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRED075"), lineoffset, scrolloffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRED076"), lineoffset, scrolloffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRED077"), lineoffset, scrolloffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRED078"), lineoffset, scrolloffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRED079"), lineoffset, scrolloffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRED080"), lineoffset, scrolloffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRED081"), lineoffset, scrolloffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRED082"), lineoffset, scrolloffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRED083"), lineoffset, scrolloffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRED084"), lineoffset, scrolloffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRED242"), lineoffset, scrolloffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRED259"), lineoffset, scrolloffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRED260"), lineoffset, scrolloffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRED261"), lineoffset, scrolloffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRED262"), lineoffset, scrolloffset);
	PrintCreditSpace(2.0, lineoffset);
	PrintCreditText(1.7, 1.0, TheText.Get("CRED085"), lineoffset, scrolloffset);
	if(CMenuManager::m_PrefsLanguage == LANGUAGE_ITALIAN)
	        PrintCreditSpace(1.5, lineoffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRED086"), lineoffset, scrolloffset);
	PrintCreditSpace(2.0, lineoffset);
	PrintCreditText(1.4, 0.82, TheText.Get("CRED087"), lineoffset, scrolloffset);
	PrintCreditSpace(1.5, lineoffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRED088"), lineoffset, scrolloffset);
	PrintCreditSpace(2.0, lineoffset);
	PrintCreditSpace(2.0, lineoffset);
	PrintCreditText(1.7, 1.0, TheText.Get("CRED089"), lineoffset, scrolloffset);
	PrintCreditSpace(1.5, lineoffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRED090"), lineoffset, scrolloffset);
	PrintCreditSpace(2.0, lineoffset);
	PrintCreditText(1.7, 1.0, TheText.Get("CRED091"), lineoffset, scrolloffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRED094"), lineoffset, scrolloffset);
	PrintCreditSpace(2.0, lineoffset);
	PrintCreditText(1.7, 1.0, TheText.Get("CRED095"), lineoffset, scrolloffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRED096"), lineoffset, scrolloffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRED097"), lineoffset, scrolloffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRED098"), lineoffset, scrolloffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRED099"), lineoffset, scrolloffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRED263"), lineoffset, scrolloffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRED264"), lineoffset, scrolloffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRED265"), lineoffset, scrolloffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRED267"), lineoffset, scrolloffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRED270"), lineoffset, scrolloffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRED266"), lineoffset, scrolloffset);
	PrintCreditSpace(2.0, lineoffset);
	PrintCreditSpace(2.0, lineoffset);
	PrintCreditText(1.4, 0.82, TheText.Get("CRED100"), lineoffset, scrolloffset);
	PrintCreditSpace(1.5, lineoffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRED101"), lineoffset, scrolloffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRED102"), lineoffset, scrolloffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRED103"), lineoffset, scrolloffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRED104"), lineoffset, scrolloffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRED105"), lineoffset, scrolloffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRED106"), lineoffset, scrolloffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRED268"), lineoffset, scrolloffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRED269"), lineoffset, scrolloffset);
	PrintCreditSpace(2.0, lineoffset);
	PrintCreditText(1.7, 1.0, TheText.Get("CRED107"), lineoffset, scrolloffset);
	PrintCreditSpace(1.5, lineoffset);
	PrintCreditText(1.0, 1.0, TheText.Get("CRED108"), lineoffset, scrolloffset);
	PrintCreditSpace(1.0, lineoffset);
	PrintCreditText(1.0, 1.0, TheText.Get("CRED109"), lineoffset, scrolloffset);
	if(CMenuManager::m_PrefsLanguage == LANGUAGE_ITALIAN)
	        PrintCreditSpace(1.0, lineoffset);
	PrintCreditText(1.0, 1.0, TheText.Get("CRED110"), lineoffset, scrolloffset);
	PrintCreditSpace(2.0, lineoffset);
	PrintCreditText(1.7, 1.0, TheText.Get("CRED111"), lineoffset, scrolloffset);
	PrintCreditText(1.0, 1.0, TheText.Get("CRED112"), lineoffset, scrolloffset);
	if(CMenuManager::m_PrefsLanguage == LANGUAGE_ITALIAN)
	        PrintCreditSpace(1.0, lineoffset);
	PrintCreditText(1.0, 1.0, TheText.Get("CRED113"), lineoffset, scrolloffset);
	if(CMenuManager::m_PrefsLanguage == LANGUAGE_ITALIAN)
	        PrintCreditSpace(1.0, lineoffset);
	PrintCreditText(1.0, 1.0, TheText.Get("CRED114"), lineoffset, scrolloffset);
	if(CMenuManager::m_PrefsLanguage == LANGUAGE_ITALIAN)
	        PrintCreditSpace(1.0, lineoffset);
	PrintCreditText(1.0, 1.0, TheText.Get("CRED115"), lineoffset, scrolloffset);
	if(CMenuManager::m_PrefsLanguage == LANGUAGE_ITALIAN)
	        PrintCreditSpace(1.0, lineoffset);
	PrintCreditText(1.0, 1.0, TheText.Get("CRED116"), lineoffset, scrolloffset);
	if(CMenuManager::m_PrefsLanguage == LANGUAGE_ITALIAN)
	        PrintCreditSpace(1.0, lineoffset);
	PrintCreditText(1.0, 1.0, TheText.Get("CRED117"), lineoffset, scrolloffset);
	if(CMenuManager::m_PrefsLanguage == LANGUAGE_ITALIAN)
	        PrintCreditSpace(1.0, lineoffset);
	PrintCreditText(1.0, 1.0, TheText.Get("CRED118"), lineoffset, scrolloffset);
	if(CMenuManager::m_PrefsLanguage == LANGUAGE_ITALIAN)
	        PrintCreditSpace(1.0, lineoffset);
	PrintCreditText(1.0, 1.0, TheText.Get("CRED119"), lineoffset, scrolloffset);
	if(CMenuManager::m_PrefsLanguage == LANGUAGE_ITALIAN)
	        PrintCreditSpace(1.0, lineoffset);
	PrintCreditText(1.0, 1.0, TheText.Get("CRED120"), lineoffset, scrolloffset);
	if(CMenuManager::m_PrefsLanguage == LANGUAGE_ITALIAN)
	        PrintCreditSpace(1.0, lineoffset);
	PrintCreditText(1.0, 1.0, TheText.Get("CRED121"), lineoffset, scrolloffset);
	if(CMenuManager::m_PrefsLanguage == LANGUAGE_ITALIAN)
	        PrintCreditSpace(1.0, lineoffset);
	PrintCreditText(1.0, 1.0, TheText.Get("CRED122"), lineoffset, scrolloffset);
	if(CMenuManager::m_PrefsLanguage == LANGUAGE_ITALIAN)
	        PrintCreditSpace(1.0, lineoffset);
	PrintCreditText(1.0, 1.0, TheText.Get("CRED123"), lineoffset, scrolloffset);
	if(CMenuManager::m_PrefsLanguage == LANGUAGE_ITALIAN)
	        PrintCreditSpace(1.0, lineoffset);
	PrintCreditText(1.0, 1.0, TheText.Get("CRED124"), lineoffset, scrolloffset);
	if(CMenuManager::m_PrefsLanguage == LANGUAGE_ITALIAN)
	        PrintCreditSpace(1.0, lineoffset);
	PrintCreditText(1.0, 1.0, TheText.Get("CRED125"), lineoffset, scrolloffset);
	if(CMenuManager::m_PrefsLanguage == LANGUAGE_ITALIAN)
	        PrintCreditSpace(1.0, lineoffset);
	PrintCreditText(1.0, 1.0, TheText.Get("CRED126"), lineoffset, scrolloffset);
	if(CMenuManager::m_PrefsLanguage == LANGUAGE_ITALIAN)
	        PrintCreditSpace(1.0, lineoffset);
	PrintCreditText(1.0, 1.0, TheText.Get("CRED127"), lineoffset, scrolloffset);
	if(CMenuManager::m_PrefsLanguage == LANGUAGE_ITALIAN)
	        PrintCreditSpace(1.0, lineoffset);
	PrintCreditText(1.0, 1.0, TheText.Get("CRED128"), lineoffset, scrolloffset);
	if(CMenuManager::m_PrefsLanguage == LANGUAGE_ITALIAN)
	        PrintCreditSpace(1.0, lineoffset);
	PrintCreditText(1.0, 1.0, TheText.Get("CRED129"), lineoffset, scrolloffset);
	if(CMenuManager::m_PrefsLanguage == LANGUAGE_ITALIAN)
	        PrintCreditSpace(1.0, lineoffset);
	PrintCreditText(1.0, 1.0, TheText.Get("CRED130"), lineoffset, scrolloffset);
	if(CMenuManager::m_PrefsLanguage == LANGUAGE_ITALIAN)
	        PrintCreditSpace(1.0, lineoffset);
	PrintCreditText(1.0, 1.0, TheText.Get("CRED131"), lineoffset, scrolloffset);
	if(CMenuManager::m_PrefsLanguage == LANGUAGE_ITALIAN)
	        PrintCreditSpace(1.0, lineoffset);
	PrintCreditText(1.0, 1.0, TheText.Get("CRED132"), lineoffset, scrolloffset);
	if(CMenuManager::m_PrefsLanguage == LANGUAGE_ITALIAN)
	        PrintCreditSpace(1.0, lineoffset);
	PrintCreditText(1.0, 1.0, TheText.Get("CRED133"), lineoffset, scrolloffset);
	if(CMenuManager::m_PrefsLanguage == LANGUAGE_ITALIAN)
	        PrintCreditSpace(1.0, lineoffset);
	PrintCreditText(1.0, 1.0, TheText.Get("CRED134"), lineoffset, scrolloffset);
	PrintCreditSpace(2.0, lineoffset);
	PrintCreditText(1.7, 1.0, TheText.Get("CRED135"), lineoffset, scrolloffset);
	PrintCreditText(1.7, 1.0, TheText.Get("CRED136"), lineoffset, scrolloffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRD136A"), lineoffset, scrolloffset);
	PrintCreditSpace(2.0, lineoffset);
	PrintCreditText(1.7, 1.0, TheText.Get("CRED137"), lineoffset, scrolloffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRD137A"), lineoffset, scrolloffset);
	PrintCreditSpace(2.0, lineoffset);
	PrintCreditText(1.7, 1.0, TheText.Get("CRED138"), lineoffset, scrolloffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRD138A"), lineoffset, scrolloffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRD138B"), lineoffset, scrolloffset);
	PrintCreditSpace(2.0, lineoffset);
	PrintCreditText(1.0, 1.0, TheText.Get("CRED139"), lineoffset, scrolloffset);
	PrintCreditSpace(2.0, lineoffset);
	PrintCreditText(1.7, 1.0, TheText.Get("CRED140"), lineoffset, scrolloffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRD140A"), lineoffset, scrolloffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRD140B"), lineoffset, scrolloffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRD140C"), lineoffset, scrolloffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRD140D"), lineoffset, scrolloffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRD140E"), lineoffset, scrolloffset);
	PrintCreditSpace(2.0, lineoffset);
	PrintCreditText(1.4, 0.82, TheText.Get("CRED141"), lineoffset, scrolloffset);
	PrintCreditText(1.0, 1.0, TheText.Get("CRED142"), lineoffset, scrolloffset);
	PrintCreditSpace(1.0, lineoffset);
	PrintCreditText(1.0, 1.0, TheText.Get("CRED143"), lineoffset, scrolloffset);
	PrintCreditSpace(1.0, lineoffset);
	PrintCreditText(1.0, 1.0, TheText.Get("CRED144"), lineoffset, scrolloffset);
	PrintCreditSpace(1.0, lineoffset);
	PrintCreditSpace(2.0, lineoffset);
	PrintCreditText(1.4, 0.82, TheText.Get("CRED145"), lineoffset, scrolloffset);
	PrintCreditText(1.4, 1.4, TheText.Get("CRED146"), lineoffset, scrolloffset);
	PrintCreditText(1.4, 1.4, TheText.Get("CRED147"), lineoffset, scrolloffset);
	PrintCreditText(1.4, 1.4, TheText.Get("CRED148"), lineoffset, scrolloffset);
	PrintCreditText(1.4, 1.4, TheText.Get("CRED149"), lineoffset, scrolloffset);
	PrintCreditText(1.4, 1.4, TheText.Get("CRED150"), lineoffset, scrolloffset);
	PrintCreditText(1.4, 1.4, TheText.Get("CRED151"), lineoffset, scrolloffset);
	PrintCreditText(1.4, 1.4, TheText.Get("CRED152"), lineoffset, scrolloffset);
	PrintCreditText(1.4, 1.4, TheText.Get("CRED153"), lineoffset, scrolloffset);
	PrintCreditText(1.4, 1.4, TheText.Get("CRED154"), lineoffset, scrolloffset);
	PrintCreditText(1.4, 1.4, TheText.Get("CRED155"), lineoffset, scrolloffset);
	PrintCreditText(1.4, 1.4, TheText.Get("CRED156"), lineoffset, scrolloffset);
	PrintCreditText(1.4, 1.4, TheText.Get("CRED157"), lineoffset, scrolloffset);
	PrintCreditText(1.4, 1.4, TheText.Get("CRED158"), lineoffset, scrolloffset);
	PrintCreditText(1.4, 1.4, TheText.Get("CRED159"), lineoffset, scrolloffset);
	PrintCreditText(1.4, 1.4, TheText.Get("CRED160"), lineoffset, scrolloffset);
	PrintCreditText(1.4, 1.4, TheText.Get("CRED161"), lineoffset, scrolloffset);
	PrintCreditText(1.4, 1.4, TheText.Get("CRED162"), lineoffset, scrolloffset);
	PrintCreditText(1.4, 1.4, TheText.Get("CRED163"), lineoffset, scrolloffset);
	PrintCreditText(1.4, 1.4, TheText.Get("CRED164"), lineoffset, scrolloffset);
	PrintCreditText(1.4, 1.4, TheText.Get("CRED165"), lineoffset, scrolloffset);
	PrintCreditText(1.4, 1.4, TheText.Get("CRED166"), lineoffset, scrolloffset);
	PrintCreditText(1.4, 1.4, TheText.Get("CRED167"), lineoffset, scrolloffset);
	PrintCreditText(1.4, 1.4, TheText.Get("CRED168"), lineoffset, scrolloffset);
	PrintCreditText(1.4, 1.4, TheText.Get("CRED169"), lineoffset, scrolloffset);
	PrintCreditText(1.4, 1.4, TheText.Get("CRED170"), lineoffset, scrolloffset);
	PrintCreditText(1.4, 1.4, TheText.Get("CRED171"), lineoffset, scrolloffset);
	PrintCreditText(1.4, 1.4, TheText.Get("CRED172"), lineoffset, scrolloffset);
	PrintCreditText(1.4, 1.4, TheText.Get("CRED173"), lineoffset, scrolloffset);
	PrintCreditText(1.4, 1.4, TheText.Get("CRED174"), lineoffset, scrolloffset);
	PrintCreditText(1.4, 1.4, TheText.Get("CRED175"), lineoffset, scrolloffset);
	PrintCreditText(1.4, 1.4, TheText.Get("CRED176"), lineoffset, scrolloffset);
	PrintCreditText(1.4, 1.4, TheText.Get("CRED177"), lineoffset, scrolloffset);
	PrintCreditText(1.4, 1.4, TheText.Get("CRED178"), lineoffset, scrolloffset);
	PrintCreditText(1.4, 1.4, TheText.Get("CRED179"), lineoffset, scrolloffset);
	PrintCreditText(1.4, 1.4, TheText.Get("CRED180"), lineoffset, scrolloffset);
	PrintCreditText(1.4, 1.4, TheText.Get("CRED181"), lineoffset, scrolloffset);
	PrintCreditText(1.4, 1.4, TheText.Get("CRED182"), lineoffset, scrolloffset);
	PrintCreditText(1.4, 1.4, TheText.Get("CRED183"), lineoffset, scrolloffset);
	PrintCreditText(1.4, 1.4, TheText.Get("CRED184"), lineoffset, scrolloffset);
	PrintCreditText(1.4, 1.4, TheText.Get("CRED185"), lineoffset, scrolloffset);
	PrintCreditText(1.4, 1.4, TheText.Get("CRED186"), lineoffset, scrolloffset);
	PrintCreditText(1.4, 1.4, TheText.Get("CRED187"), lineoffset, scrolloffset);
	PrintCreditText(1.4, 1.4, TheText.Get("CRED188"), lineoffset, scrolloffset);
	PrintCreditText(1.4, 1.4, TheText.Get("CRED189"), lineoffset, scrolloffset);
	PrintCreditText(1.4, 1.4, TheText.Get("CRED190"), lineoffset, scrolloffset);
	PrintCreditText(1.4, 1.4, TheText.Get("CRED191"), lineoffset, scrolloffset);
	PrintCreditText(1.4, 1.4, TheText.Get("CRED192"), lineoffset, scrolloffset);
	PrintCreditText(1.4, 1.4, TheText.Get("CRED193"), lineoffset, scrolloffset);
	PrintCreditText(1.4, 1.4, TheText.Get("CRED194"), lineoffset, scrolloffset);
	PrintCreditText(1.4, 1.4, TheText.Get("CRED195"), lineoffset, scrolloffset);
	PrintCreditText(1.4, 1.4, TheText.Get("CRED196"), lineoffset, scrolloffset);
	PrintCreditText(1.4, 1.4, TheText.Get("CRED197"), lineoffset, scrolloffset);
	PrintCreditText(1.4, 1.4, TheText.Get("CRED198"), lineoffset, scrolloffset);
	PrintCreditText(1.4, 1.4, TheText.Get("CRED199"), lineoffset, scrolloffset);
	PrintCreditText(1.4, 1.4, TheText.Get("CRED200"), lineoffset, scrolloffset);
	PrintCreditText(1.4, 1.4, TheText.Get("CRED201"), lineoffset, scrolloffset);
	PrintCreditText(1.4, 1.4, TheText.Get("CRED202"), lineoffset, scrolloffset);
	PrintCreditText(1.4, 1.4, TheText.Get("CRED203"), lineoffset, scrolloffset);
	PrintCreditText(1.4, 1.4, TheText.Get("CRED204"), lineoffset, scrolloffset);
	PrintCreditText(1.4, 1.4, TheText.Get("CRED205"), lineoffset, scrolloffset);
	PrintCreditText(1.4, 1.4, TheText.Get("CRED206"), lineoffset, scrolloffset);
	PrintCreditText(1.4, 1.4, TheText.Get("CRED207"), lineoffset, scrolloffset);
	PrintCreditText(1.4, 1.4, TheText.Get("CRED208"), lineoffset, scrolloffset);
	PrintCreditText(1.4, 1.4, TheText.Get("CRED209"), lineoffset, scrolloffset);
	PrintCreditText(1.4, 1.4, TheText.Get("CRED210"), lineoffset, scrolloffset);
	PrintCreditText(1.4, 1.4, TheText.Get("CRED211"), lineoffset, scrolloffset);
	PrintCreditText(1.4, 1.4, TheText.Get("CRED212"), lineoffset, scrolloffset);
	PrintCreditText(1.4, 1.4, TheText.Get("CRED213"), lineoffset, scrolloffset);
	PrintCreditText(1.4, 1.4, TheText.Get("CRED214"), lineoffset, scrolloffset);
	PrintCreditText(1.4, 1.4, TheText.Get("CRED215"), lineoffset, scrolloffset);
	PrintCreditText(1.4, 1.4, TheText.Get("CRED216"), lineoffset, scrolloffset);
	PrintCreditText(1.4, 1.4, TheText.Get("CRED241"), lineoffset, scrolloffset);
	PrintCreditSpace(2.0, lineoffset);
	PrintCreditText(1.4, 0.82, TheText.Get("CRED217"), lineoffset, scrolloffset);
	PrintCreditSpace(1.5, lineoffset);
	PrintCreditSpace(2.0, lineoffset);
	PrintCreditText(1.4, 0.82, TheText.Get("CRED218"), lineoffset, scrolloffset);
	PrintCreditSpace(1.5, lineoffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRD218A"), lineoffset, scrolloffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRD218B"), lineoffset, scrolloffset);
	PrintCreditSpace(2.0, lineoffset);
	PrintCreditText(1.4, 0.82, TheText.Get("CRED219"), lineoffset, scrolloffset);
	PrintCreditSpace(1.5, lineoffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRED220"), lineoffset, scrolloffset);
	PrintCreditSpace(2.0, lineoffset);
	PrintCreditText(1.4, 0.82, TheText.Get("CRED221"), lineoffset, scrolloffset);
	PrintCreditSpace(1.5, lineoffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRED222"), lineoffset, scrolloffset);
	PrintCreditSpace(2.0, lineoffset);
	PrintCreditText(1.4, 0.82, TheText.Get("CRED223"), lineoffset, scrolloffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRED224"), lineoffset, scrolloffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRED225"), lineoffset, scrolloffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRED226"), lineoffset, scrolloffset);
	PrintCreditSpace(2.0, lineoffset);
	PrintCreditText(1.4, 0.82, TheText.Get("CRED227"), lineoffset, scrolloffset);
	PrintCreditSpace(1.5, lineoffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRED228"), lineoffset, scrolloffset);
	PrintCreditText(1.7, 1.7, TheText.Get("CRED229"), lineoffset, scrolloffset);
	PrintCreditSpace(2.0, lineoffset);
	PrintCreditText(1.4, 0.82, TheText.Get("CRED230"), lineoffset, scrolloffset);
	PrintCreditText(1.4, 1.4, TheText.Get("CRED231"), lineoffset, scrolloffset);
	PrintCreditText(1.4, 1.4, TheText.Get("CRED232"), lineoffset, scrolloffset);
	PrintCreditText(1.4, 1.4, TheText.Get("CRED233"), lineoffset, scrolloffset);
	PrintCreditText(1.4, 1.4, TheText.Get("CRED234"), lineoffset, scrolloffset);
	PrintCreditText(1.4, 1.4, TheText.Get("CRED235"), lineoffset, scrolloffset);
	PrintCreditText(1.4, 1.4, TheText.Get("CRED236"), lineoffset, scrolloffset);
	PrintCreditText(1.4, 1.4, TheText.Get("CRED237"), lineoffset, scrolloffset);
	PrintCreditText(1.4, 1.4, TheText.Get("CRED238"), lineoffset, scrolloffset);
	PrintCreditText(1.4, 1.4, TheText.Get("CRED239"), lineoffset, scrolloffset);
	PrintCreditText(1.4, 1.4, TheText.Get("CRED240"), lineoffset, scrolloffset);
	PrintCreditText(1.4, 1.4, TheText.Get("LITTLE"), lineoffset, scrolloffset);
	PrintCreditText(1.4, 1.4, TheText.Get("NICK"), lineoffset, scrolloffset);
	PrintCreditText(1.4, 1.4, TheText.Get("CRED243"), lineoffset, scrolloffset);
	PrintCreditText(1.4, 1.4, TheText.Get("CRED244"), lineoffset, scrolloffset);
	PrintCreditSpace(2.0, lineoffset);
	PrintCreditSpace(2.0, lineoffset);


	CFont::DrawFonts();
	if(TheCamera.m_WideScreenOn)
		TheCamera.DrawBordersForWideScreen();

	if(lineoffset + SCREEN_HEIGHT - scrolloffset < -10.0f)
		bCreditsGoing = false;
}

bool CCredits::AreCreditsDone(void)
{
	return !bCreditsGoing;
}

STARTPATCHES
	InjectHook(0x4FE7A0, CCredits::Init, PATCH_JUMP);
	InjectHook(0x4FE760, CCredits::Start, PATCH_JUMP);
	InjectHook(0x4FE780, CCredits::Stop, PATCH_JUMP);
	InjectHook(0x4FE790, CCredits::AreCreditsDone, PATCH_JUMP);
	InjectHook(0x4FADF0, CCredits::Render, PATCH_JUMP);
	InjectHook(0x4FE710, CCredits::PrintCreditSpace, PATCH_JUMP);
	InjectHook(0x4FE620, CCredits::PrintCreditText, PATCH_JUMP);
ENDPATCHES
