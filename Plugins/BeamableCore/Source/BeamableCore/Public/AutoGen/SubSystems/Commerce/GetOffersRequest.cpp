
#include "GetOffersRequest.h"

void UGetOffersRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetOffersRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/object/commerce/{objectId}/offers");
	Route = Route.Replace(TEXT("{objectId}"), *FString::FromInt(ObjectId));
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	if(Language.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		QueryParams.Appendf(TEXT("%s=%s"), *TEXT("language"), *Language.Val);
		bIsFirstQueryParam = false;
	}

	if(Time.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		QueryParams.Appendf(TEXT("%s=%s"), *TEXT("time"), *Time.Val);
		bIsFirstQueryParam = false;
	}

	if(Stores.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		QueryParams.Appendf(TEXT("%s=%s"), *TEXT("stores"), *Stores.Val);
		bIsFirstQueryParam = false;
	}

	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetOffersRequest::BuildBody(FString& BodyString) const
{
	
}

UGetOffersRequest* UGetOffersRequest::MakeGetOffersRequest(int64 _ObjectId, FOptionalString _Language, FOptionalString _Time, FOptionalString _Stores, UObject* Outer)
{
	UGetOffersRequest* Req = NewObject<UGetOffersRequest>(Outer);

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ObjectId = _ObjectId;
	Req->Language = _Language;
	Req->Time = _Time;
	Req->Stores = _Stores;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
