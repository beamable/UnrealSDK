
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/CreateDonationRequestBody.h"
#include "BeamableCore/Public/AutoGen/EmptyResponse.h"

#include "PostDonationsRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostDonationsRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id", Category="Beam")
	int64 ObjectId = {};
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UCreateDonationRequestBody* Body = {};

	// Beam Base Request Declaration
	UPostDonationsRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Groups|Utils|Make/Break", DisplayName="Make PostDonations",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_Config,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPostDonationsRequest* Make(int64 _ObjectId, FString _CurrencyId, int64 _Amount, FOptionalString _Config, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostDonationsSuccess, FBeamRequestContext, Context, UPostDonationsRequest*, Request, UEmptyResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostDonationsError, FBeamRequestContext, Context, UPostDonationsRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostDonationsComplete, FBeamRequestContext, Context, UPostDonationsRequest*, Request);

using FPostDonationsFullResponse = FBeamFullResponse<UPostDonationsRequest*, UEmptyResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostDonationsFullResponse, FPostDonationsFullResponse);
