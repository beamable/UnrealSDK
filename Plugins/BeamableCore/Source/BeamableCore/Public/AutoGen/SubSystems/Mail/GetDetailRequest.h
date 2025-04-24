
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/MailResponse.h"

#include "GetDetailRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetDetailRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id", Category="Beam")
	int64 ObjectId = {};
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Mid", Category="Beam")
	int64 Mid = {};

	// Body Params
	

	// Beam Base Request Declaration
	UGetDetailRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Mail|Utils|Make/Break", DisplayName="Make GetDetail",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UGetDetailRequest* Make(int64 _ObjectId, int64 _Mid, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetDetailSuccess, FBeamRequestContext, Context, UGetDetailRequest*, Request, UMailResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetDetailError, FBeamRequestContext, Context, UGetDetailRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetDetailComplete, FBeamRequestContext, Context, UGetDetailRequest*, Request);

using FGetDetailFullResponse = FBeamFullResponse<UGetDetailRequest*, UMailResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetDetailFullResponse, FGetDetailFullResponse);
