
#include "BeamableCore/Public/AutoGen/SubSystems/Session/GetHistoryRequest.h"

void UGetHistoryRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetHistoryRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/session/history");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
	QueryParams.Appendf(TEXT("%s=%s"), TEXT("dbid"), *FString::FromInt(Dbid));
	bIsFirstQueryParam = false;
	
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

void UGetHistoryRequest::BuildBody(FString& BodyString) const
{
	
}

UGetHistoryRequest* UGetHistoryRequest::Make(int64 _Dbid, FOptionalInt32 _Month, FOptionalInt32 _Year, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UGetHistoryRequest* Req = NewObject<UGetHistoryRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->Dbid = _Dbid;
	Req->Month = _Month;
	Req->Year = _Year;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
