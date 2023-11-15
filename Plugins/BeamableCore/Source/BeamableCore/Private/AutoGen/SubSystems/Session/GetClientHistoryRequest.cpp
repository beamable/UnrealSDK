
#include "BeamableCore/Public/AutoGen/SubSystems/Session/GetClientHistoryRequest.h"

void UGetClientHistoryRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetClientHistoryRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/session/client/history");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	if(Month.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		QueryParams.Appendf(TEXT("%s=%s"), TEXT("month"), *FString::FromInt(Month.Val));
		bIsFirstQueryParam = false;
	}

	if(Year.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		QueryParams.Appendf(TEXT("%s=%s"), TEXT("year"), *FString::FromInt(Year.Val));
		bIsFirstQueryParam = false;
	}

	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetClientHistoryRequest::BuildBody(FString& BodyString) const
{
	
}

UGetClientHistoryRequest* UGetClientHistoryRequest::Make(FOptionalInt32 _Month, FOptionalInt32 _Year, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UGetClientHistoryRequest* Req = NewObject<UGetClientHistoryRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->Month = _Month;
	Req->Year = _Year;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
