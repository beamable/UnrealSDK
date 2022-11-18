
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"



#include "AutoGen/MatchMakingMatchesPvpResponse.h"

#include "GetMatchesRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetMatchesRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id", Category="Beam")
	FString ObjectId;
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Pool Size", Category="Beam")
	int32 PoolSize;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Windows", Category="Beam")
	int32 Windows;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Window Size", Category="Beam")
	int32 WindowSize;

	// Body Params
	

	// Beam Base Request Declaration
	UGetMatchesRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Backend|Leaderboards", DisplayName="Beam - Make GetMatches",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner"))
	static UGetMatchesRequest* Make(FString _ObjectId, int32 _PoolSize, int32 _Windows, int32 _WindowSize, UObject* RequestOwner);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetMatchesSuccess, FBeamRequestContext, Context, UGetMatchesRequest*, Request, UMatchMakingMatchesPvpResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetMatchesError, FBeamRequestContext, Context, UGetMatchesRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetMatchesComplete, FBeamRequestContext, Context, UGetMatchesRequest*, Request);

using FGetMatchesFullResponse = FBeamFullResponse<UGetMatchesRequest*, UMatchMakingMatchesPvpResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetMatchesFullResponse, FGetMatchesFullResponse);
