
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/GetGameResponse.h"

#include "GetGameRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetGameRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Root PID")
	FString RootPID;

	// Body Params
	

	// Beam Base Request Declaration
	UGetGameRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UGetGameRequest* MakeGetGameRequest(FString _RootPID, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetGameSuccess, FBeamRequestContext, Context, UGetGameRequest*, Request, UGetGameResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetGameError, FBeamRequestContext, Context, UGetGameRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetGameComplete, FBeamRequestContext, Context, UGetGameRequest*, Request);

using FGetGameFullResponse = FBeamFullResponse<UGetGameRequest*, UGetGameResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetGameFullResponse, FGetGameFullResponse);
