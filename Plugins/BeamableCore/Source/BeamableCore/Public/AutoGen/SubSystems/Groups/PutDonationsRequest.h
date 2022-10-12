
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/MakeDonationRequestBody.h"
#include "AutoGen/EmptyResponse.h"

#include "PutDonationsRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPutDonationsRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id")
	int64 ObjectId;
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="")
	UMakeDonationRequestBody* Body;

	// Beam Base Request Declaration
	UPutDonationsRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="_bAutoClaim,Outer"))
	static UPutDonationsRequest* MakePutDonationsRequest(int64 _ObjectId, int64 _RecipientId, int64 _Amount, FOptionalBool _bAutoClaim, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutDonationsSuccess, FBeamRequestContext, Context, UPutDonationsRequest*, Request, UEmptyResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutDonationsError, FBeamRequestContext, Context, UPutDonationsRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPutDonationsComplete, FBeamRequestContext, Context, UPutDonationsRequest*, Request);

using FPutDonationsFullResponse = FBeamFullResponse<UPutDonationsRequest*, UEmptyResponse*>;
DECLARE_DELEGATE_OneParam(FOnPutDonationsFullResponse, FPutDonationsFullResponse);
