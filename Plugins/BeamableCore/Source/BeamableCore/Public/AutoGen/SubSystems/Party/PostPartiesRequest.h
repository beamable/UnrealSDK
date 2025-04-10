
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/CreateParty.h"
#include "BeamableCore/Public/AutoGen/Party.h"

#include "PostPartiesRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostPartiesRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UCreateParty* Body = {};

	// Beam Base Request Declaration
	UPostPartiesRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Party|Utils|Make/Break", DisplayName="Make PostParties",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_Restriction,_Leader,_MaxSize,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPostPartiesRequest* Make(FOptionalString _Restriction, FOptionalBeamGamerTag _Leader, FOptionalInt32 _MaxSize, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostPartiesSuccess, FBeamRequestContext, Context, UPostPartiesRequest*, Request, UParty*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostPartiesError, FBeamRequestContext, Context, UPostPartiesRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostPartiesComplete, FBeamRequestContext, Context, UPostPartiesRequest*, Request);

using FPostPartiesFullResponse = FBeamFullResponse<UPostPartiesRequest*, UParty*>;
DECLARE_DELEGATE_OneParam(FOnPostPartiesFullResponse, FPostPartiesFullResponse);
