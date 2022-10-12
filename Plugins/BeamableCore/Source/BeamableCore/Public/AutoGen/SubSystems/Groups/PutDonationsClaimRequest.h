
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/EmptyResponse.h"

#include "PutDonationsClaimRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPutDonationsClaimRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id")
	int64 ObjectId;
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UPutDonationsClaimRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UPutDonationsClaimRequest* MakePutDonationsClaimRequest(int64 _ObjectId, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutDonationsClaimSuccess, FBeamRequestContext, Context, UPutDonationsClaimRequest*, Request, UEmptyResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutDonationsClaimError, FBeamRequestContext, Context, UPutDonationsClaimRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPutDonationsClaimComplete, FBeamRequestContext, Context, UPutDonationsClaimRequest*, Request);

using FPutDonationsClaimFullResponse = FBeamFullResponse<UPutDonationsClaimRequest*, UEmptyResponse*>;
DECLARE_DELEGATE_OneParam(FOnPutDonationsClaimFullResponse, FPutDonationsClaimFullResponse);
