
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalInt32.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalInt64.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalBool.h"
#include "BeamableCore/Public/AutoGen/LeaderBoardViewResponse.h"

#include "GetViewRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetViewRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id", Category="Beam")
	FString ObjectId = {};
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Max", Category="Beam")
	FOptionalInt32 Max = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Focus", Category="Beam")
	FOptionalInt64 Focus = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Friends", Category="Beam")
	FOptionalBool bFriends = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="From", Category="Beam")
	FOptionalInt32 From = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Outlier", Category="Beam")
	FOptionalInt64 Outlier = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Guild", Category="Beam")
	FOptionalBool bGuild = {};

	// Body Params
	

	// Beam Base Request Declaration
	UGetViewRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Leaderboards|Utils|Make/Break", DisplayName="Make GetView",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_Max,_Focus,_bFriends,_From,_Outlier,_bGuild,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UGetViewRequest* Make(FString _ObjectId, FOptionalInt32 _Max, FOptionalInt64 _Focus, FOptionalBool _bFriends, FOptionalInt32 _From, FOptionalInt64 _Outlier, FOptionalBool _bGuild, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetViewSuccess, FBeamRequestContext, Context, UGetViewRequest*, Request, ULeaderBoardViewResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetViewError, FBeamRequestContext, Context, UGetViewRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetViewComplete, FBeamRequestContext, Context, UGetViewRequest*, Request);

using FGetViewFullResponse = FBeamFullResponse<UGetViewRequest*, ULeaderBoardViewResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetViewFullResponse, FGetViewFullResponse);
