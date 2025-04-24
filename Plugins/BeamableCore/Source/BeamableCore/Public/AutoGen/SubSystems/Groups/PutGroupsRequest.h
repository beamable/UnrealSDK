
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/GroupUpdate.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#include "PutGroupsRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPutGroupsRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id", Category="Beam")
	int64 ObjectId = {};
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UGroupUpdate* Body = {};

	// Beam Base Request Declaration
	UPutGroupsRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Groups|Utils|Make/Break", DisplayName="Make PutGroups",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_Name,_EnrollmentType,_Tag,_Slogan,_Requirement,_Motd,_ClientData,_SubGroup,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPutGroupsRequest* Make(int64 _ObjectId, FOptionalString _Name, FOptionalString _EnrollmentType, FOptionalString _Tag, FOptionalString _Slogan, FOptionalInt64 _Requirement, FOptionalString _Motd, FOptionalString _ClientData, FOptionalInt64 _SubGroup, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutGroupsSuccess, FBeamRequestContext, Context, UPutGroupsRequest*, Request, UCommonResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutGroupsError, FBeamRequestContext, Context, UPutGroupsRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPutGroupsComplete, FBeamRequestContext, Context, UPutGroupsRequest*, Request);

using FPutGroupsFullResponse = FBeamFullResponse<UPutGroupsRequest*, UCommonResponse*>;
DECLARE_DELEGATE_OneParam(FOnPutGroupsFullResponse, FPutGroupsFullResponse);
