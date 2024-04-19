
#include "BeamableCore/Public/AutoGen/SubSystems/Mail/GetDetailRequest.h"

void UGetDetailRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetDetailRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/object/mail/{objectId}/detail");
	Route = Route.Replace(TEXT("{objectId}"), *FString::Printf(TEXT("%lld"), ObjectId));
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
	QueryParams.Appendf(TEXT("%s=%s"), TEXT("mid"), *FString::FromInt(Mid));
	bIsFirstQueryParam = false;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetDetailRequest::BuildBody(FString& BodyString) const
{
	
}

UGetDetailRequest* UGetDetailRequest::Make(int64 _ObjectId, int64 _Mid, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UGetDetailRequest* Req = NewObject<UGetDetailRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ObjectId = _ObjectId;
	Req->Mid = _Mid;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
