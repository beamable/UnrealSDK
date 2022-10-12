
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"



#include "AutoGen/Optionals/OptionalString.h"
#include "AutoGen/ActiveListingResponse.h"

#include "GetListingsRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetListingsRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id")
	int64 ObjectId;
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Listing")
	FString Listing;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Store")
	FOptionalString Store;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Time")
	FOptionalString Time;

	// Body Params
	

	// Beam Base Request Declaration
	UGetListingsRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="_Store,_Time,Outer"))
	static UGetListingsRequest* MakeGetListingsRequest(int64 _ObjectId, FString _Listing, FOptionalString _Store, FOptionalString _Time, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetListingsSuccess, FBeamRequestContext, Context, UGetListingsRequest*, Request, UActiveListingResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetListingsError, FBeamRequestContext, Context, UGetListingsRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetListingsComplete, FBeamRequestContext, Context, UGetListingsRequest*, Request);

using FGetListingsFullResponse = FBeamFullResponse<UGetListingsRequest*, UActiveListingResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetListingsFullResponse, FGetListingsFullResponse);
