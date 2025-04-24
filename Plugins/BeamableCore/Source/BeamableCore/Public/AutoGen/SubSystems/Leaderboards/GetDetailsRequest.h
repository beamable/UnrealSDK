
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalInt32.h"
#include "BeamableCore/Public/AutoGen/LeaderboardDetails.h"

#include "GetDetailsRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetDetailsRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id", Category="Beam")
	FString ObjectId = {};
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="From", Category="Beam")
	FOptionalInt32 From = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Max", Category="Beam")
	FOptionalInt32 Max = {};

	// Body Params
	

	// Beam Base Request Declaration
	UGetDetailsRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Leaderboards|Utils|Make/Break", DisplayName="Make GetDetails",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_From,_Max,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UGetDetailsRequest* Make(FString _ObjectId, FOptionalInt32 _From, FOptionalInt32 _Max, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetDetailsSuccess, FBeamRequestContext, Context, UGetDetailsRequest*, Request, ULeaderboardDetails*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetDetailsError, FBeamRequestContext, Context, UGetDetailsRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetDetailsComplete, FBeamRequestContext, Context, UGetDetailsRequest*, Request);

using FGetDetailsFullResponse = FBeamFullResponse<UGetDetailsRequest*, ULeaderboardDetails*>;
DECLARE_DELEGATE_OneParam(FOnGetDetailsFullResponse, FGetDetailsFullResponse);
