
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamBackend/SemanticTypes/BeamPid.h"
#include "BeamableCore/Public/AutoGen/GetGameResponse.h"

#include "GetGameRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetGameRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Root PID", Category="Beam")
	FBeamPid RootPID = {};

	// Body Params
	

	// Beam Base Request Declaration
	UGetGameRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Realms|Utils|Make/Break", DisplayName="Make GetGame",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UGetGameRequest* Make(FBeamPid _RootPID, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetGameSuccess, FBeamRequestContext, Context, UGetGameRequest*, Request, UGetGameResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetGameError, FBeamRequestContext, Context, UGetGameRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetGameComplete, FBeamRequestContext, Context, UGetGameRequest*, Request);

using FGetGameFullResponse = FBeamFullResponse<UGetGameRequest*, UGetGameResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetGameFullResponse, FGetGameFullResponse);
