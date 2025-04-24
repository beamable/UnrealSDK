
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/PromoteNewLeader.h"
#include "BeamableCore/Public/AutoGen/Party.h"

#include "PutPromoteRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPutPromoteRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Id", Category="Beam")
	FGuid Id = {};
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UPromoteNewLeader* Body = {};

	// Beam Base Request Declaration
	UPutPromoteRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Party|Utils|Make/Break", DisplayName="Make PutPromote",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_PlayerId,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPutPromoteRequest* Make(FGuid _Id, FOptionalBeamGamerTag _PlayerId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutPromoteSuccess, FBeamRequestContext, Context, UPutPromoteRequest*, Request, UParty*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutPromoteError, FBeamRequestContext, Context, UPutPromoteRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPutPromoteComplete, FBeamRequestContext, Context, UPutPromoteRequest*, Request);

using FPutPromoteFullResponse = FBeamFullResponse<UPutPromoteRequest*, UParty*>;
DECLARE_DELEGATE_OneParam(FOnPutPromoteFullResponse, FPutPromoteFullResponse);
