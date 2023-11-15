
#include "BeamableCore/Public/AutoGen/SubSystems/Cloudsaving/GetCloudsavingRequest.h"

void UGetCloudsavingRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetCloudsavingRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/cloudsaving/");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	if(PlayerId.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		QueryParams.Appendf(TEXT("%s=%s"), TEXT("playerId"), *FString::FromInt(PlayerId.Val));
		bIsFirstQueryParam = false;
	}

	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetCloudsavingRequest::BuildBody(FString& BodyString) const
{
	
}

UGetCloudsavingRequest* UGetCloudsavingRequest::Make(FOptionalInt64 _PlayerId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UGetCloudsavingRequest* Req = NewObject<UGetCloudsavingRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->PlayerId = _PlayerId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
