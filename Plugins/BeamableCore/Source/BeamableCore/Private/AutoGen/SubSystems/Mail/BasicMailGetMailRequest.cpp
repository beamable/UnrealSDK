
#include "BeamableCore/Public/AutoGen/SubSystems/Mail/BasicMailGetMailRequest.h"

void UBasicMailGetMailRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UBasicMailGetMailRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/mail/");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
	QueryParams.Appendf(TEXT("%s=%s"), TEXT("mid"), *FString::FromInt(Mid));
	bIsFirstQueryParam = false;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UBasicMailGetMailRequest::BuildBody(FString& BodyString) const
{
	
}

UBasicMailGetMailRequest* UBasicMailGetMailRequest::Make(int64 _Mid, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UBasicMailGetMailRequest* Req = NewObject<UBasicMailGetMailRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->Mid = _Mid;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
