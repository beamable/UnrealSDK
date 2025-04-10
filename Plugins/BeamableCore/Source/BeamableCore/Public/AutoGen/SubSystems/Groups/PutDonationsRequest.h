
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/MakeDonationRequestBody.h"
#include "BeamableCore/Public/AutoGen/EmptyResponse.h"

#include "PutDonationsRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPutDonationsRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id", Category="Beam")
	int64 ObjectId = {};
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UMakeDonationRequestBody* Body = {};

	// Beam Base Request Declaration
	UPutDonationsRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Groups|Utils|Make/Break", DisplayName="Make PutDonations",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_bAutoClaim,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPutDonationsRequest* Make(int64 _ObjectId, int64 _RecipientId, int64 _Amount, FOptionalBool _bAutoClaim, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutDonationsSuccess, FBeamRequestContext, Context, UPutDonationsRequest*, Request, UEmptyResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutDonationsError, FBeamRequestContext, Context, UPutDonationsRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPutDonationsComplete, FBeamRequestContext, Context, UPutDonationsRequest*, Request);

using FPutDonationsFullResponse = FBeamFullResponse<UPutDonationsRequest*, UEmptyResponse*>;
DECLARE_DELEGATE_OneParam(FOnPutDonationsFullResponse, FPutDonationsFullResponse);
