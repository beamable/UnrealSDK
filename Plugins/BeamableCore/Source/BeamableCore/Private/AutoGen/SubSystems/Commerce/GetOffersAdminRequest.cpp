
#include "BeamableCore/Public/AutoGen/SubSystems/Commerce/GetOffersAdminRequest.h"

void UGetOffersAdminRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetOffersAdminRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/object/commerce/{objectId}/offersAdmin");
	Route = Route.Replace(TEXT("{objectId}"), *FString::Printf(TEXT("%lld"), ObjectId));
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	if(Language.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		QueryParams.Appendf(TEXT("%s=%s"), TEXT("language"), *Language.Val);
		bIsFirstQueryParam = false;
	}

	if(Time.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		QueryParams.Appendf(TEXT("%s=%s"), TEXT("time"), *Time.Val);
		bIsFirstQueryParam = false;
	}

	if(Stores.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		QueryParams.Appendf(TEXT("%s=%s"), TEXT("stores"), *Stores.Val);
		bIsFirstQueryParam = false;
	}

	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetOffersAdminRequest::BuildBody(FString& BodyString) const
{
	
}

UGetOffersAdminRequest* UGetOffersAdminRequest::Make(int64 _ObjectId, FOptionalString _Language, FOptionalString _Time, FOptionalString _Stores, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UGetOffersAdminRequest* Req = NewObject<UGetOffersAdminRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ObjectId = _ObjectId;
	Req->Language = _Language;
	Req->Time = _Time;
	Req->Stores = _Stores;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
