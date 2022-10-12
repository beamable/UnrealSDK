
#include "GetListingsRequest.h"

void UGetListingsRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetListingsRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/object/commerce/{objectId}/listings");
	Route = Route.Replace(TEXT("{objectId}"), *FString::FromInt(ObjectId));
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
	QueryParams.Appendf(TEXT("%s=%s"), *TEXT("listing"), *Listing);
	bIsFirstQueryParam = false;
	
	if(Store.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		QueryParams.Appendf(TEXT("%s=%s"), *TEXT("store"), *Store.Val);
		bIsFirstQueryParam = false;
	}

	if(Time.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		QueryParams.Appendf(TEXT("%s=%s"), *TEXT("time"), *Time.Val);
		bIsFirstQueryParam = false;
	}

	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetListingsRequest::BuildBody(FString& BodyString) const
{
	
}

UGetListingsRequest* UGetListingsRequest::MakeGetListingsRequest(int64 _ObjectId, FString _Listing, FOptionalString _Store, FOptionalString _Time, UObject* Outer)
{
	UGetListingsRequest* Req = NewObject<UGetListingsRequest>(Outer);

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ObjectId = _ObjectId;
	Req->Listing = _Listing;
	Req->Store = _Store;
	Req->Time = _Time;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
