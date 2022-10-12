
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/MatchUpdate.h"

#include "GetMatchRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetMatchRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id")
	int64 ObjectId;
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UGetMatchRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UGetMatchRequest* MakeGetMatchRequest(int64 _ObjectId, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetMatchSuccess, FBeamRequestContext, Context, UGetMatchRequest*, Request, UMatchUpdate*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetMatchError, FBeamRequestContext, Context, UGetMatchRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetMatchComplete, FBeamRequestContext, Context, UGetMatchRequest*, Request);

using FGetMatchFullResponse = FBeamFullResponse<UGetMatchRequest*, UMatchUpdate*>;
DECLARE_DELEGATE_OneParam(FOnGetMatchFullResponse, FGetMatchFullResponse);
