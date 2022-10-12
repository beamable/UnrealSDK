
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/Optionals/OptionalInt32.h"
#include "AutoGen/LeaderboardDetails.h"

#include "GetDetailsRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetDetailsRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id")
	FString ObjectId;
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="From")
	FOptionalInt32 From;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Max")
	FOptionalInt32 Max;

	// Body Params
	

	// Beam Base Request Declaration
	UGetDetailsRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="_From,_Max,Outer"))
	static UGetDetailsRequest* MakeGetDetailsRequest(FString _ObjectId, FOptionalInt32 _From, FOptionalInt32 _Max, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetDetailsSuccess, FBeamRequestContext, Context, UGetDetailsRequest*, Request, ULeaderboardDetails*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetDetailsError, FBeamRequestContext, Context, UGetDetailsRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetDetailsComplete, FBeamRequestContext, Context, UGetDetailsRequest*, Request);

using FGetDetailsFullResponse = FBeamFullResponse<UGetDetailsRequest*, ULeaderboardDetails*>;
DECLARE_DELEGATE_OneParam(FOnGetDetailsFullResponse, FGetDetailsFullResponse);
