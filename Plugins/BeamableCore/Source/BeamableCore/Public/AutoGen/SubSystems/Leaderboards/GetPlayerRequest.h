
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/ListLeaderBoardViewResponse.h"

#include "GetPlayerRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetPlayerRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Dbid")
	int64 Dbid;

	// Body Params
	

	// Beam Base Request Declaration
	UGetPlayerRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UGetPlayerRequest* MakeGetPlayerRequest(int64 _Dbid, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetPlayerSuccess, FBeamRequestContext, Context, UGetPlayerRequest*, Request, UListLeaderBoardViewResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetPlayerError, FBeamRequestContext, Context, UGetPlayerRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetPlayerComplete, FBeamRequestContext, Context, UGetPlayerRequest*, Request);

using FGetPlayerFullResponse = FBeamFullResponse<UGetPlayerRequest*, UListLeaderBoardViewResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetPlayerFullResponse, FGetPlayerFullResponse);
