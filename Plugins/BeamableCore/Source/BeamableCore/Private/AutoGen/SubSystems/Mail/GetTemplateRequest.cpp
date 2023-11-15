
#include "BeamableCore/Public/AutoGen/SubSystems/Mail/GetTemplateRequest.h"

void UGetTemplateRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetTemplateRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/mail/template");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
	QueryParams.Appendf(TEXT("%s=%s"), TEXT("templateName"), *TemplateName);
	bIsFirstQueryParam = false;
	
	bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
	QueryParams.Appendf(TEXT("%s=%s"), TEXT("gamerTag"), *FString::FromInt(GamerTag));
	bIsFirstQueryParam = false;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetTemplateRequest::BuildBody(FString& BodyString) const
{
	
}

UGetTemplateRequest* UGetTemplateRequest::Make(FString _TemplateName, int64 _GamerTag, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UGetTemplateRequest* Req = NewObject<UGetTemplateRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->TemplateName = _TemplateName;
	Req->GamerTag = _GamerTag;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
