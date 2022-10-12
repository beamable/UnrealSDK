
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/CreateDonationRequestBody.h"
#include "AutoGen/EmptyResponse.h"

#include "PostDonationsRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostDonationsRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id")
	int64 ObjectId;
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="")
	UCreateDonationRequestBody* Body;

	// Beam Base Request Declaration
	UPostDonationsRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="_Config,Outer"))
	static UPostDonationsRequest* MakePostDonationsRequest(int64 _ObjectId, FString _CurrencyId, int64 _Amount, FOptionalString _Config, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostDonationsSuccess, FBeamRequestContext, Context, UPostDonationsRequest*, Request, UEmptyResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostDonationsError, FBeamRequestContext, Context, UPostDonationsRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostDonationsComplete, FBeamRequestContext, Context, UPostDonationsRequest*, Request);

using FPostDonationsFullResponse = FBeamFullResponse<UPostDonationsRequest*, UEmptyResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostDonationsFullResponse, FPostDonationsFullResponse);
