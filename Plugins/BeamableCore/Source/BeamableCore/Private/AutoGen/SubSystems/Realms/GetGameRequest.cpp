
#include "BeamableCore/Public/AutoGen/SubSystems/Realms/GetGameRequest.h"

void UGetGameRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetGameRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/realms/game");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
	QueryParams.Appendf(TEXT("%s=%s"), TEXT("rootPID"), *static_cast<FString>(RootPID));
	bIsFirstQueryParam = false;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetGameRequest::BuildBody(FString& BodyString) const
{
	
}

UGetGameRequest* UGetGameRequest::Make(FBeamPid _RootPID, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UGetGameRequest* Req = NewObject<UGetGameRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->RootPID = _RootPID;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
