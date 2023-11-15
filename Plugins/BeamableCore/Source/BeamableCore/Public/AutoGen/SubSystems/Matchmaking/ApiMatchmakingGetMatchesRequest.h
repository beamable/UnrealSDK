
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"


#include "BeamableCore/Public/AutoGen/Match.h"

#include "ApiMatchmakingGetMatchesRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UApiMatchmakingGetMatchesRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Id", Category="Beam")
	FGuid Id = {};
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UApiMatchmakingGetMatchesRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Backend|Matchmaking", DisplayName="Beam - Make ApiMatchmakingGetMatches",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UApiMatchmakingGetMatchesRequest* Make(FGuid _Id, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnApiMatchmakingGetMatchesSuccess, FBeamRequestContext, Context, UApiMatchmakingGetMatchesRequest*, Request, UMatch*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnApiMatchmakingGetMatchesError, FBeamRequestContext, Context, UApiMatchmakingGetMatchesRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnApiMatchmakingGetMatchesComplete, FBeamRequestContext, Context, UApiMatchmakingGetMatchesRequest*, Request);

using FApiMatchmakingGetMatchesFullResponse = FBeamFullResponse<UApiMatchmakingGetMatchesRequest*, UMatch*>;
DECLARE_DELEGATE_OneParam(FOnApiMatchmakingGetMatchesFullResponse, FApiMatchmakingGetMatchesFullResponse);
