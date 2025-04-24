
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/Match.h"

#include "ApiMatchmakingGetMatchesByIdRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UApiMatchmakingGetMatchesByIdRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Id", Category="Beam")
	FGuid Id = {};
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UApiMatchmakingGetMatchesByIdRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Matchmaking|Utils|Make/Break", DisplayName="Make ApiMatchmakingGetMatchesById",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UApiMatchmakingGetMatchesByIdRequest* Make(FGuid _Id, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnApiMatchmakingGetMatchesByIdSuccess, FBeamRequestContext, Context, UApiMatchmakingGetMatchesByIdRequest*, Request, UMatch*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnApiMatchmakingGetMatchesByIdError, FBeamRequestContext, Context, UApiMatchmakingGetMatchesByIdRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnApiMatchmakingGetMatchesByIdComplete, FBeamRequestContext, Context, UApiMatchmakingGetMatchesByIdRequest*, Request);

using FApiMatchmakingGetMatchesByIdFullResponse = FBeamFullResponse<UApiMatchmakingGetMatchesByIdRequest*, UMatch*>;
DECLARE_DELEGATE_OneParam(FOnApiMatchmakingGetMatchesByIdFullResponse, FApiMatchmakingGetMatchesByIdFullResponse);
